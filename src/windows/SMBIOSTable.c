/*
* Copyright (C) 2019 MadStrawberry
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial 
* portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <SMBIOSTable.h>

#include <assert.h>

#include <WbemIdl.h>

#include <ComPtr.h>
#include <SMBIOSType.h>

#pragma comment(lib, "WbemUuid.lib")

typedef struct _WbemStructure
{
	IWbemClassObject*		object_ptr;
	IEnumWbemClassObject*	enum_result_ptr;
	IWbemLocator*			locator_ptr;
	IWbemServices*			services_ptr;
} WbemStructure;

struct _SMBIOSTableData
{
	uint8_t   version_major;
	uint8_t   version_minor;

	uint8_t*  smbios_buffer;
	uint32_t  smbios_buffer_size;
};

static int  kWMIInitialize = 0;

static int  wmi_init(WbemStructure** wmi_object);

static int  wmi_execute_query(WbemStructure* wmi_object, BSTR wql);

static int  wmi_get_enumerate(WbemStructure* wmi_object);

static int  wmi_get_result(WbemStructure* wmi_object, LPCWSTR field, struct tagVARIANT* result, CIMTYPE* type);

static void wmi_destroy(WbemStructure* wmi_object);

int wmi_init(WbemStructure** wmi_object)
{
	HRESULT hr = S_OK;

	assert(*wmi_object == NULL);

	if (kWMIInitialize)
		return 0;
	
	/* init object*/
	(*wmi_object) = (WbemStructure*)malloc(sizeof(WbemStructure));
	(*wmi_object)->object_ptr = NULL;
	(*wmi_object)->enum_result_ptr = NULL;
	(*wmi_object)->locator_ptr = NULL;
	(*wmi_object)->services_ptr = NULL;

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (FAILED(hr))
	{
		hr = CoInitialize(NULL);

		if (FAILED(hr))
			return 0;
	}

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

	if (!(SUCCEEDED(hr) || hr == RPC_E_TOO_LATE))
		return 0;

	hr = CoCreateInstance(&CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, &IID_IWbemLocator, (void**)(&(*wmi_object)->locator_ptr));

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE((*wmi_object)->locator_ptr);

		return 0;
	}
	
	hr = HDC_COM_OBJECT((*wmi_object)->locator_ptr)->ConnectServer((*wmi_object)->locator_ptr, L"root\\WMI", NULL, NULL, 0, 0, 0, 0, &(*wmi_object)->services_ptr);

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE((*wmi_object)->services_ptr);

		return 0;
	}

	hr = CoSetProxyBlanket((struct IUnknown*)(*wmi_object)->services_ptr, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE((*wmi_object)->services_ptr);

		return 0;
	}

	kWMIInitialize = 1;
	
	return 1;
}

int wmi_execute_query(WbemStructure* wmi_object, BSTR wql)
{
	HRESULT hr = S_OK;
	
	assert(wmi_object->services_ptr != NULL);

	hr = HDC_COM_OBJECT(wmi_object->services_ptr)->ExecQuery(wmi_object->services_ptr, L"WQL", wql,
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &(wmi_object->enum_result_ptr));

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE(wmi_object->enum_result_ptr);
		
		return 0;
	}

	return 1;
}

int wmi_get_enumerate(WbemStructure* wmi_object)
{
	HRESULT hr = S_OK;
	
	ULONG result = 0;

	assert(wmi_object->enum_result_ptr != NULL);

	hr = HDC_COM_OBJECT(wmi_object->enum_result_ptr)->Next(wmi_object->enum_result_ptr, WBEM_INFINITE, 1, &(wmi_object->object_ptr), &result);

	if (FAILED(hr) || 0 == result || wmi_object->object_ptr == NULL)
	{
		HDC_COM_PTR_RELEASE(wmi_object->object_ptr);
		
		return 0;
	}

	return 1;
}

int wmi_get_result(WbemStructure* wmi_object, LPCWSTR field, struct tagVARIANT* result, CIMTYPE* type)
{
	HRESULT hr = S_OK;
	
	assert(wmi_object->object_ptr != NULL);

	hr = HDC_COM_OBJECT(wmi_object->object_ptr)->Get(wmi_object->object_ptr, field, 0, result, type, 0);

	if (FAILED(hr))
	{
		VariantClear(result);
		
		return 0;
	}

	return 1;
}

void wmi_destroy(WbemStructure* wmi_object)
{
	assert(wmi_object != NULL);
	
	HDC_COM_PTR_RELEASE(wmi_object->object_ptr);
	HDC_COM_PTR_RELEASE(wmi_object->enum_result_ptr);
	HDC_COM_PTR_RELEASE(wmi_object->locator_ptr);
	HDC_COM_PTR_RELEASE(wmi_object->services_ptr);

	kWMIInitialize = 0;
}

int HDC_CALLBACK_API hdc_smbios_find_rom(SMBIOSTableData* table_data)
{
	int enumerate_result = 0;
	WbemStructure* wbem = NULL;

	assert(table_data != NULL);

	if (!wmi_init(&wbem))
		return 0;

	if (!wmi_execute_query(wbem, L"select * from MSSMBios_RawSMBiosTables"))
		return 0;

	enumerate_result = wmi_get_enumerate(wbem);
	
	if (enumerate_result)
	{
		struct tagVARIANT value;

		wmi_get_result(wbem, L"SmbiosMajorVersion", &value, NULL);
		table_data->version_major = value.bVal;

		wmi_get_result(wbem, L"SmbiosMinorVersion", &value, NULL);
		table_data->version_minor = value.bVal;

		wmi_get_result(wbem, L"SMBiosData", &value, NULL);

		assert((VT_UI1 | VT_ARRAY) == value.vt);

		SAFEARRAY* safe_array = V_ARRAY(&value);

		table_data->smbios_buffer = (uint8_t*)(safe_array->pvData);
		table_data->smbios_buffer_size = safe_array->rgsabound[0].cElements;
	}

	wmi_destroy(wbem);

	return enumerate_result;
}

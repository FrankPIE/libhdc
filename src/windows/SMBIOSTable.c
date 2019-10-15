/*
* Copyright (C) 2019 MadStrawberry
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* ����
* The above copyright notice and this permission notice shall be included in all copies or substantial 
* portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/
#include <ComPtr.h>
#include <SMBIOSType.h>

#include <comdef.h>
#include <windows.h>
#include <WbemIdl.h>

#include <assert.h>

#pragma comment(lib, "WbemUuid.lib")

typedef struct _WbemStructure
{
	IWbemClassObject*		object_ptr_;
	IEnumWbemClassObject*	enum_result_ptr_;
	IWbemLocator*			locator_ptr_;
	IWbemServices*			services_ptr_;
} WbemStructure;

static int  wmi_init(WbemStructure** wmi_object);

static int  wmi_execute_query(WbemStructure* wmi_object, BSTR wql);

static int  wmi_get_enumerate(WbemStructure* wmi_object);

static int  wmi_get_result(WbemStructure* wmi_object, LPCWSTR field, struct tagVARIANT* result, CIMTYPE* type);

static void wmi_destroy(WbemStructure* wmi_object);

int wmi_init(WbemStructure** wmi_object)
{
	HRESULT hr = S_OK;

	assert(*wmi_object == NULL);

	/* init object*/
	(*wmi_object) = (WbemStructure*)malloc(sizeof(WbemStructure));
	(*wmi_object)->object_ptr_ = NULL;
	(*wmi_object)->enum_result_ptr_ = NULL;
	(*wmi_object)->locator_ptr_ = NULL;
	(*wmi_object)->services_ptr_ = NULL;

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

	hr = CoCreateInstance(&CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, &IID_IWbemLocator, (void**)(&(*wmi_object)->locator_ptr_));

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE((*wmi_object)->locator_ptr_);

		return 0;
	}
	
	hr = HDC_COM_OBJECT((*wmi_object)->locator_ptr_)->ConnectServer((*wmi_object)->locator_ptr_, L"root\\WMI", NULL, NULL, 0, 0, 0, 0, &(*wmi_object)->services_ptr_);

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE((*wmi_object)->services_ptr_);

		return 0;
	}

	hr = CoSetProxyBlanket((struct IUnknown*)(*wmi_object)->services_ptr_, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE((*wmi_object)->services_ptr_);

		return 0;
	}

	return 1;
}

int wmi_execute_query(WbemStructure* wmi_object, BSTR wql)
{
	HRESULT hr = S_OK;
	
	assert(wmi_object->services_ptr_ != NULL);

	hr = HDC_COM_OBJECT(wmi_object->services_ptr_)->ExecQuery(wmi_object->services_ptr_, L"WQL", wql,
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &(wmi_object->enum_result_ptr_));

	if (FAILED(hr))
	{
		HDC_COM_PTR_RELEASE(wmi_object->enum_result_ptr_);
		
		return 0;
	}

	return 1;
}

int wmi_get_enumerate(WbemStructure* wmi_object)
{
	HRESULT hr = S_OK;
	
	ULONG result = 0;

	assert(wmi_object->enum_result_ptr_ != NULL);

	hr = HDC_COM_OBJECT(wmi_object->enum_result_ptr_)->Next(wmi_object->enum_result_ptr_, WBEM_INFINITE, 1, &(wmi_object->object_ptr_), &result);

	if (FAILED(hr) || 0 == result || wmi_object->object_ptr_ == NULL)
	{
		HDC_COM_PTR_RELEASE(wmi_object->object_ptr_);
		
		return 0;
	}

	return 1;
}

int wmi_get_result(WbemStructure* wmi_object, LPCWSTR field, struct tagVARIANT* result, CIMTYPE* type)
{
	HRESULT hr = S_OK;
	
	assert(wmi_object->object_ptr_ != NULL);

	hr = HDC_COM_OBJECT(wmi_object->object_ptr_)->Get(wmi_object->object_ptr_, field, 0, result, type, 0);

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
	
	HDC_COM_PTR_RELEASE(wmi_object->object_ptr_);
	HDC_COM_PTR_RELEASE(wmi_object->enum_result_ptr_);
	HDC_COM_PTR_RELEASE(wmi_object->locator_ptr_);
	HDC_COM_PTR_RELEASE(wmi_object->services_ptr_);
}

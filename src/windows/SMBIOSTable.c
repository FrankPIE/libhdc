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

#define MAX_STRING_ARRAY_SIZE 255

typedef struct _WbemStructure
{
	IWbemClassObject*		object_ptr;
	IEnumWbemClassObject*	enum_result_ptr;
	IWbemLocator*			locator_ptr;
	IWbemServices*			services_ptr;
} WbemStructure;

struct _SMBIOSTable
{
	uint8_t		 type;
	uint32_t	 offset;
	uint8_t		 data_size;
	uint16_t	 real_size;
	const char*  string_array[MAX_STRING_ARRAY_SIZE];
	
	struct _SMBIOSTable* next;
};

struct _SMBIOSTableData
{
	uint8_t   version_major;
	uint8_t   version_minor;

	uint8_t*  smbios_buffer;
	uint32_t  smbios_buffer_size;

	struct _SMBIOSTable* table_index;

	struct _SMBIOSTable* table_list;
};

static int  kWMIInitialize = 0;

static int  wmi_init(WbemStructure** wmi_object);

static int  wmi_execute_query(WbemStructure* wmi_object, BSTR wql);

static int  wmi_get_enumerate(WbemStructure* wmi_object);

static int  wmi_get_result(WbemStructure* wmi_object, LPCWSTR field, struct tagVARIANT* result, CIMTYPE* type);

static void wmi_destroy(WbemStructure* wmi_object);

static int smbios_find_first_target_type(SMBIOSTableData* table_data, uint8_t target_type);

static int smbios_find_next_target_type(SMBIOSTableData* table_data);

static void smbios_get_data_field(SMBIOSTableData* table_data, void** dst, uint8_t id);

static const char* smbios_get_string_field(SMBIOSTableData* table_data, uint8_t id);

int wmi_init(WbemStructure** wmi_object)
{
	HRESULT hr = S_OK;

	assert(*wmi_object == NULL);

	if (kWMIInitialize)
		return 0;
	
	/* init object*/
	(*wmi_object) = (WbemStructure*)malloc(sizeof(WbemStructure));

	if (*wmi_object)
	{
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
	
	return 0;
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

	free(wmi_object);
	
	kWMIInitialize = 0;
}

int smbios_find_first_target_type(SMBIOSTableData* table_data, uint8_t target_type)
{
	assert(table_data != NULL);

	struct _SMBIOSTable* iterator = table_data->table_list;

	while (iterator)
	{
		if (iterator->type == target_type)
		{
			table_data->table_index = iterator;
			return 1;
		}

		iterator = iterator->next;
	}

	return 0;
}

int smbios_find_next_target_type(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	table_data->table_index = table_data->table_index->next;

	return table_data->table_index != NULL;
}

void smbios_collect_string_array(SMBIOSTableData* table_data, struct _SMBIOSTable* node)
{
	size_t index = 0;
	
	uint8_t* begin = table_data->smbios_buffer + node->offset;

	begin += node->data_size - 1;

	uint8_t* string_array_iterator = begin;

	while (string_array_iterator != begin + node->real_size + 1)
	{
		if (string_array_iterator == begin || *string_array_iterator == '\0')
			node->string_array[index++] = (const char*)(string_array_iterator + 1);

		++string_array_iterator;
	}
}

void smbios_get_data_field(SMBIOSTableData* table_data, void** dst, uint8_t id)
{
	assert(table_data->table_index != NULL);
	
	*dst = table_data->smbios_buffer + table_data->table_index->offset + id;

	assert(id > 0 && id < table_data->table_index->data_size);
}

const char* smbios_get_string_field(SMBIOSTableData* table_data, uint8_t id)
{
	assert(id > 0 && id < table_data->table_index->data_size);

	const size_t index = table_data->smbios_buffer[table_data->table_index->offset + id];
	
	return table_data->table_index->string_array[index - 1];
}

int HDC_CALLBACK_API hdc_smbios_init(SMBIOSTableData** table_data)
{
	*table_data = (SMBIOSTableData*)malloc(sizeof(SMBIOSTableData));

	if (*table_data)
	{
		int enumerate_result = 0;
		WbemStructure* wbem = NULL;

		(*table_data)->table_list = NULL;
		(*table_data)->table_index = NULL;

		if (!wmi_init(&wbem))
			return 0;

		if (!wmi_execute_query(wbem, L"select * from MSSMBios_RawSMBiosTables"))
			return 0;

		enumerate_result = wmi_get_enumerate(wbem);

		if (enumerate_result)
		{
			uint32_t smbios_buffer_index = 0;
			struct tagVARIANT value;

			wmi_get_result(wbem, L"SmbiosMajorVersion", &value, NULL);
			(*table_data)->version_major = value.bVal;

			wmi_get_result(wbem, L"SmbiosMinorVersion", &value, NULL);
			(*table_data)->version_minor = value.bVal;

			wmi_get_result(wbem, L"SMBiosData", &value, NULL);

			assert((VT_UI1 | VT_ARRAY) == value.vt);

			SAFEARRAY* safe_array = V_ARRAY(&value);

			(*table_data)->smbios_buffer = (uint8_t*)(safe_array->pvData);
			(*table_data)->smbios_buffer_size = safe_array->rgsabound[0].cElements;

			while (smbios_buffer_index < (*table_data)->smbios_buffer_size)
			{
				struct _SMBIOSTable* table_info = (struct _SMBIOSTable*)malloc(sizeof(struct _SMBIOSTable));

				if (table_info)
				{
					struct _SMBIOSTable** last_node = &(*table_data)->table_list;
					uint8_t* eof = NULL;
					
					table_info->offset = smbios_buffer_index;
					table_info->type = (*table_data)->smbios_buffer[smbios_buffer_index];
					table_info->data_size = (*table_data)->smbios_buffer[smbios_buffer_index + 1];
					table_info->real_size = table_info->data_size;
					memset((void*)table_info->string_array, 0, sizeof(table_info->string_array));
					table_info->next = NULL;

					eof = (*table_data)->smbios_buffer + smbios_buffer_index;

					// in win32 16bit 0 is the eof label
					while ((*(uint16_t*)(eof + table_info->real_size)) != 0)
						++table_info->real_size;

					table_info->real_size += 2;

					smbios_collect_string_array(*table_data, table_info);
										
					smbios_buffer_index += table_info->real_size;

					while (*last_node)
						last_node = &(*last_node)->next;

					*last_node = table_info;					
				}				
			}
		}

		wmi_destroy(wbem);

		return enumerate_result;
	}

	return 0;
}

const char* __stdcall hdc_smbios_bios_vendor(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	if (smbios_find_first_target_type(table_data, SMBIOS_TYPE0_BIOS))
		return smbios_get_string_field(table_data, SMBIOS_TYPE0_VENDOR_STRING);

	return NULL;
}

const char* __stdcall hdc_smbios_bios_version(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	if (smbios_find_first_target_type(table_data, SMBIOS_TYPE0_BIOS))
		return smbios_get_string_field(table_data, SMBIOS_TYPE0_VERSION_STRING);

	return NULL;

}

const char* __stdcall hdc_smbios_bios_release_date(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	if (smbios_find_first_target_type(table_data, SMBIOS_TYPE0_BIOS))
		return smbios_get_string_field(table_data, SMBIOS_TYPE0_RELEASE_DATE_STRING);

	return NULL;
}

int HDC_CALLBACK_API hdc_smbios_system_uuid(SMBIOSTableData* table_data, SMBIOS_UUID* uuid)
{
	assert(table_data != NULL);
	assert(sizeof(*uuid) == 16);

	if (smbios_find_first_target_type(table_data, SMBIOS_TYPE1_SYSTEM))
	{
		uint8_t *uuid_data_buffer = NULL;

		smbios_get_data_field(table_data, (void**)&uuid_data_buffer, SMBIOS_TYPE1_UUID_16BYTE);

		memcpy(uuid->uuid, uuid_data_buffer, sizeof(*uuid));

		return 1;
	}

	return 0;
}

const char* HDC_CALLBACK_API hdc_smbios_baseboard_manufacturer(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	if (smbios_find_first_target_type(table_data, SMBIOS_TYPE2_BASEBOARD))
		return smbios_get_string_field(table_data, SMBIOS_TYPE2_MANUFACTURER_STRING);

	return NULL;
}

const char* __stdcall hdc_smbios_baseboard_product(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	if (smbios_find_first_target_type(table_data, SMBIOS_TYPE2_BASEBOARD))
		return smbios_get_string_field(table_data, SMBIOS_TYPE2_PRODUCT_STRING);

	return NULL;
}

void HDC_CALLBACK_API hdc_smbios_destroy(SMBIOSTableData* table_data)
{
	assert(table_data != NULL);

	struct _SMBIOSTable* head = table_data->table_list;
	struct _SMBIOSTable* iterator = NULL;

	while (head)
	{
		iterator = head;
		head = head->next;

		free(iterator);		
	}

	free(table_data);
}

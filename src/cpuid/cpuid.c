/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <cpuid/cpuid.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cpuid/cpuid_type.h>
#include <cpuid/cpuid_handle.h>

#include <common/errorc.h>
#include <common/hashmap.h>

extern bool		   cpuid_flag_check();
extern void		   cpuid(uint32_t registers[4], uint32_t function_id);

/* ***********************implement*********************** */

hash_map_t* cpuid_vendor_table()
{
	hash_map_t* hash_map = NULL;

	const int intel_flag = HDC_CPU_VENDOR_INTEL;
	const int amd_flag = HDC_CPU_VENDOR_AMD;

	hash_map_item_t table[] =
	{
		make_pair(make_string_key("GenuineIntel"), make_buffer_value((void*)&intel_flag, sizeof(int))),
		make_pair(make_string_key("AuthenticAMD"), make_buffer_value((void*)&amd_flag, sizeof(int))),
	};

	hash_map_init(&hash_map, table, sizeof(table) / sizeof(hash_map_item_t));

	return hash_map;
}

int hdc_cpuid_init(cpuid_handle_t** handle)
{
	assert(*handle == NULL);

	char vendor[13] = { '\0' };

	hdc_cpu_register_t cpu_info = { 0u };
	hash_map_item_t    item = { 0 };

	hash_map_t* vendor_map = cpuid_vendor_table();

	if (!cpuid_flag_check())
		return HDC_EC_CPUID_NOT_SUPPORT;

	cpuid(cpu_info.registers, 0);

	memcpy(vendor, &cpu_info.ebx, 4);
	memcpy(vendor + 8, &cpu_info.ecx, 4);
	memcpy(vendor + 4, &cpu_info.edx, 4);

	item.key = make_string_key(vendor);

	hash_map_find(vendor_map, item.key, (value_t*)&item.value);

	switch (*(int*)item.value)
	{
	case HDC_CPU_VENDOR_INTEL:
		*handle = intel_cpuid_handle_init();
		break;

	default:
		break;
	}

	if (*handle == NULL)
		return HDC_EC_BAD_ALLOC;

	if (vendor_map)
		hash_map_destroy(vendor_map);

	return HDC_SUCCESS;
}

int hdc_cpuid_vendor_type(cpuid_handle_t* handle)
{
	return 0;
}

const char* hdc_cpuid_identify(cpuid_handle_t* handle)
{
	if(strlen(handle->identify) == 0)
		handle->vptrt.get_cpuid_identify_string(handle, handle->identify);
	
	return handle->identify;
}

bool hdc_cpuid_serial_number_support(cpuid_handle_t* handle)
{
	return false;
}

int hdc_cpuid_serial_number(cpuid_handle_t* handle, hdc_uuid_t* uuid)
{
	handle->vptrt.get_cpuid_serial_number(handle, uuid);
	
	return HDC_SUCCESS;
}

void hdc_cpuid_destroy(cpuid_handle_t* handle)
{
	if (handle)
	{
		switch (handle->vendor_type)
		{
		case HDC_CPU_VENDOR_INTEL:
			intel_cpuid_handle_destroy(handle);
			break;

		default:
			break;
		}
	}
}

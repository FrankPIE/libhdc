/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <cpuid/cpuid.h>

#include <common/hashmap.h>

/* ***********************interface*********************** */

extern bool		   cpuid_flag_check();
extern void		   cpuid(uint32_t registers[4], uint32_t function_id);

extern hash_map_t* cpuid_vendor_table();

extern void		   intel_cpuid_identify_string(cpuid_handle_t* handle);
extern hash_map_t* intel_cpuid_brand_id_table();

/* ***********************structure*********************** */

typedef void(*identify_function_t)(cpuid_handle_t*);

struct _cpuid_function_helper_t
{
	identify_function_t  identify_function;
};

struct _cpuid_handle_t
{
	bool		 cpuid_support;
	int			 vendor_type;
	char		 identify[49];
	unsigned int largest_standard_function_number;

	hash_map_t*  vendor_map;
	hash_map_t*  brand_id_map;

	struct _cpuid_function_helper_t functions;
};

/* ***********************implement*********************** */

void check_vendor(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	char vendor[13] = { '\0' };
	hdc_cpu_register_t cpu_info = { 0U };
	hash_map_item_t item = { 0 };

	cpuid(cpu_info.registers, 0);

	(handle)->largest_standard_function_number = cpu_info.eax;

	memcpy(vendor, &cpu_info.ebx, 4);
	memcpy(vendor + 8, &cpu_info.ecx, 4);
	memcpy(vendor + 4, &cpu_info.edx, 4);

	item.key = make_string_key(vendor);

	hash_map_find(handle->vendor_map, item.key, (value_t*)&item.value);

	handle->vendor_type = item.value != NULL ? *(int*)item.value : HDC_CPU_VENDOR_UNKNOWN;

	switch (handle->vendor_type)
	{
	case HDC_CPU_VENDOR_INTEL:
		handle->brand_id_map = intel_cpuid_brand_id_table();
		handle->functions.identify_function = intel_cpuid_identify_string;
		break;

	default:
		break;
	}
}

extern cpuid_handle_t* cpuid_handle_init()
{
	cpuid_handle_t* handle = (cpuid_handle_t*)malloc(sizeof(cpuid_handle_t));
	
	if (!handle)
		return NULL;

	memset(handle, 0, sizeof(cpuid_handle_t));
	memset(handle->identify, '\0', sizeof(handle->identify));

	handle->cpuid_support = cpuid_flag_check();

	handle->vendor_map = cpuid_vendor_table();

	check_vendor(handle);

	return handle;
}

extern bool cpuid_handle_cpuid_support(cpuid_handle_t* handle)
{
	assert(handle != NULL);
	
	return handle->cpuid_support;
}

extern int cpuid_handle_vendor_type(cpuid_handle_t* handle)
{
	assert(handle != NULL);

	return handle->vendor_type;
}

extern char* cpuid_handle_identify_string(cpuid_handle_t* handle)
{
	assert(handle != NULL);

	return handle->identify;
}

extern char* cpuid_identify_string(cpuid_handle_t* handle)
{
	assert(handle != NULL);

	handle->functions.identify_function(handle);

	return handle->identify;
}

extern hash_map_t* cpuid_handle_brand_id_map(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	return handle->brand_id_map;
}

extern void cpuid_handle_destroy(cpuid_handle_t* handle)
{
	if (handle)
	{		
		hash_map_destroy(handle->vendor_map);

		free(handle);
	}
}

/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_HANDLE_H_
#define _HDC_CPUID_HANDLE_H_

#include <cpuid/cpuid.h>

#include <common/hashmap.h>

struct _cpuid_handle_virtual_table_ptr_t
{
	void (*get_cpuid_identify_string)(cpuid_handle_t* handle, char* buffer);

	void (*get_cpuid_serial_number)(cpuid_handle_t* handle, hdc_uuid_t* buffer);

	int  (*get_cpuid_standard_function_number)(cpuid_handle_t* handle);

	bool (*is_cpuid_serial_number_support)(cpuid_handle_t* handle);
};

struct _cpuid_handle_t
{
	struct _cpuid_handle_virtual_table_ptr_t vptrt;

	bool cpuid_support;
	int  vendor_type;
	char identify[49];
};

struct _intel_cpuid_handle_t
{
	struct _cpuid_handle_t super;

	hash_map_t*  brand_index_map;
};

struct _amd_cpuid_handle_t
{
	struct _cpuid_handle_t super;
};

struct _arm_cpuid_handle_t
{
	struct _cpuid_handle_t super;
};

cpuid_handle_t* intel_cpuid_handle_init();

cpuid_handle_t* amd_cpuid_handle_init();

cpuid_handle_t* arm_cpuid_handle_init();

void			intel_cpuid_handle_destroy(cpuid_handle_t* handle);

#endif
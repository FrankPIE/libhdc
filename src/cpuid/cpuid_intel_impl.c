/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include <cpuid/cpuid.h>
#include <common/hashmap.h>

/* ***********************interface*********************** */

/* cpuid_instructs */
extern void cpuid(uint32_t registers[4], uint32_t function_id);

/* handle */
extern char*       cpuid_handle_identify_string(cpuid_handle_t* handle);
extern bool        cpuid_handle_cpuid_support(cpuid_handle_t* handle);
extern hash_map_t* cpuid_handle_brand_id_map (cpuid_handle_t* handle);

/* ***********************implement*********************** */

bool intel_cpuid_brand_string(char* buffer)
{
	hdc_cpu_register_t cpu_register = { 0U };

	cpuid(cpu_register.registers, 0x80000000);

	if (cpu_register.eax >= 0x80000004)
	{
		cpuid(cpu_register.registers, 0x80000002);
		memcpy(buffer, cpu_register.registers, 16);

		cpuid(cpu_register.registers, 0x80000003);
		memcpy(buffer + 16, cpu_register.registers, 16);

		cpuid(cpu_register.registers, 0x80000004);
		memcpy(buffer + 32, cpu_register.registers, 16);

		return true;
	}

	return false;
}

bool intel_cpuid_brand_id(char* buffer, hash_map_t* brand_id_map)
{
	unsigned int flag = 0;
	hdc_cpu_register_t cpu_register = { 0U };

	cpuid(cpu_register.registers, 1);

	flag = cpu_register.ebx & 0xFF;

	if (flag != 0)
	{
		if (flag == 0x03 && cpu_register.eax == 0x06B1)
			flag = 0x05;

		if (flag == 0x0b && cpu_register.eax == 0x0F13)
			flag = 0x0d;

		if (flag == 0x0e && cpu_register.eax == 0x0F13)
			flag = 0x10;

		if (brand_id_map)
		{
			char* brand_string = NULL;

			hash_map_find(brand_id_map, make_buffer_key((unsigned char*)&flag, sizeof(flag)), (void**)&brand_string);

			memcpy(buffer, brand_string, strlen(brand_string));
		}

		return true;
	}

	return false;
}

extern void intel_cpuid_identify_string(cpuid_handle_t* handle)
{
	char* buffer = NULL;

	assert(cpuid_handle_cpuid_support(handle));

	buffer = cpuid_handle_identify_string(handle);

	if (strlen(buffer) != 0)
		return;

	if (intel_cpuid_brand_string(buffer))
		return;

	if (intel_cpuid_brand_id(buffer, cpuid_handle_brand_id_map(handle)))
		return;
	
	strcpy(buffer, "UnSupported");
}
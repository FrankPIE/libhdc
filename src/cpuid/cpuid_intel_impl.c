/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include <cpuid/cpuid.h>
#include <cpuid/cpuid_type.h>
#include <cpuid/cpuid_handle.h>

#include <common/hashmap.h>

/* ***********************interface*********************** */

/* cpuid_instructs */
extern void cpuid(uint32_t registers[4], uint32_t function_id);

/* ***********************implement*********************** */
hash_map_t* intel_cpuid_brand_index_table()
{
#define MakeIndexIncrement (++index, sizeof(int))
	hash_map_t* hash_map = NULL;

	int index = 0x01;

	hash_map_item_t table[] =
	{
		//index == 01h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		//index == 02h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III processor")),

		//index == 03h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III Xeon(R) processor")),

		//index == 04h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III processor")),

		// index == 05h, equal index == 03h and signature = 0x06B1
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 06h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Pentium(R) III processor-M")),

		// index == 07h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 08h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) 4 processor")),

		// index == 09h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) 4 processor")),

		// index == 0Ah
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 0Bh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor")),

		// index == 0Ch
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor MP")),

		// index == 0Dh, equal index == 0Bh and signature = 0x0F13
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor MP")),

		// index == 0Eh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Pentium(R) 4 processor-M")),

		// index == 0Fh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 10h, equal index == 0Eh and signature = 0x0F13
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor")),

		// index == 11h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Genuine Intel(R) processor")),

		// index == 12h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron M processor")),

		// index == 13h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 14h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 15h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Genuine Intel(R) processor")),

		// index == 16h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) M processor")),

		// index == 17h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),
	};

	hash_map_init(&hash_map, table, sizeof(table) / sizeof(hash_map_item_t));

#undef MakeIndexIncrement
	return hash_map;
}


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

void intel_cpuid_identify_string(cpuid_handle_t* handle, char* buffer)
{
	assert(handle->cpuid_support);

	if (strlen(buffer) != 0)
		return;

	if (intel_cpuid_brand_string(buffer))
		return;

	if (intel_cpuid_brand_id(buffer, ((struct _intel_cpuid_handle_t*)handle)->brand_index_map))
		return;
	
	strcpy(buffer, "UnSupported");
}

bool intel_cpuid_feature_flag_ecx(int flag)
{
	hdc_cpu_register_t cpu_register = { 0U };

	cpuid(cpu_register.registers, 1);

	return (cpu_register.ecx & flag);
}

bool intel_cpuid_feature_flag_edx(int flag)
{
	hdc_cpu_register_t cpu_register = { 0U };

	cpuid(cpu_register.registers, 1);

	return (cpu_register.edx & flag);
}

void intel_cpuid_serial_number(cpuid_handle_t* handle, hdc_uuid_t* uuid)
{
	hdc_cpu_register_t cpu_register = { 0U };

	assert(handle->cpuid_support);

	memset(uuid->uuid, 0, 16);

	cpuid(cpu_register.registers, 1);
	
	if (cpu_register.edx & HDC_CPUID_INTEL_PSN_FLAG)
	{
		memcpy(uuid->uuid + 4, &cpu_register.eax, 4);

		cpuid(cpu_register.registers, 3);

		memcpy(uuid->uuid + 8, &cpu_register.edx, 4);

		memcpy(uuid->uuid + 12, &cpu_register.ecx, 4);
	}
}

cpuid_handle_t* intel_cpuid_handle_init()
{
	struct _intel_cpuid_handle_t* handle = (struct _intel_cpuid_handle_t*)malloc(sizeof(struct _intel_cpuid_handle_t));

	if (handle)
	{
		handle->super.cpuid_support = true;

		handle->super.vendor_type = HDC_CPU_VENDOR_INTEL;

		memset(handle->super.identify, '\0', sizeof(handle->super.identify));
		
		handle->brand_index_map = intel_cpuid_brand_index_table();

		handle->super.vptrt.get_cpuid_identify_string = intel_cpuid_identify_string;
		handle->super.vptrt.get_cpuid_serial_number   = intel_cpuid_serial_number;

		return (cpuid_handle_t*)handle;
	}

	return NULL;
}

void intel_cpuid_handle_destroy(cpuid_handle_t* handle)
{
	if (handle)
	{
		hash_map_destroy(((struct _intel_cpuid_handle_t*)handle)->brand_index_map);

		free(handle);
	}
}

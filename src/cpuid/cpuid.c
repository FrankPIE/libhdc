/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <cpuid/cpuid.h>

#include <assert.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

typedef struct _hdc_cpu_register_t
{
	union
	{
		struct
		{
			unsigned int eax;
			unsigned int ebx;
			unsigned int ecx;
			unsigned int edx;
		};

		unsigned int registers[4];
	};
} hdc_cpu_register_t;

struct _cpuid_handle_t
{
	CPUVendor	 vendor_type;

	char	     vendor[13];
	char		 identify[49];
	unsigned int largest_standard_function_number;
};

/*  */
extern unsigned int kCPUIDFlag;

extern void _cpuid_check();

extern void _cpuid(unsigned int[4]);

static bool is_cpuid_support();
static void get_vendor_name(cpuid_handle_t* handle);

static bool is_cpuid_support()
{
	_cpuid_check();

	return kCPUIDFlag == 0x200000;
}

void get_vendor_name(cpuid_handle_t* handle)
{
	hdc_cpu_register_t cpu_info = { 0U };

	cpu_info.eax = 0;
	_cpuid(cpu_info.registers);

	(handle)->largest_standard_function_number = cpu_info.eax;

	memcpy((handle)->vendor, &cpu_info.ebx, 4);
	memcpy((handle)->vendor + 8, &cpu_info.ecx, 4);
	memcpy((handle)->vendor + 4, &cpu_info.edx, 4);

	(handle)->vendor[12] = '\0';

	if (strcmp(handle->vendor, "GenuineIntel") == 0)
	{
		handle->vendor_type = CPU_INTEL;
	}
	else if(strcmp(handle->vendor, "AuthenticAMD") == 0)
	{
		handle->vendor_type = CPU_AMD;
	}
	else 
	{
		handle->vendor_type = CPU_UNKNOWN;
	}
}

int hdc_cpuid_init(cpuid_handle_t** handle)
{
	assert(*handle == NULL);

	cpuid_handle_t* handle_ptr = NULL;

	*handle = (cpuid_handle_t*)malloc(sizeof(cpuid_handle_t));

	handle_ptr = *handle;

	if (!*handle)
		return 0;

	if (!is_cpuid_support())
		return 0;

	get_vendor_name(handle_ptr);

	return 1;
}

void hdc_cpuid_destroy(cpuid_handle_t* handle)
{
}

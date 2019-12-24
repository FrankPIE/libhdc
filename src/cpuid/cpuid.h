/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_H_
#define _HDC_CPUID_H_

#define HDC_CPU_VENDOR_UNKNOWN 0
#define HDC_CPU_VENDOR_INTEL   1
#define HDC_CPU_VENDOR_AMD	   2
#define HDC_CPU_VENDOR_ARM     3

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

typedef struct _cpuid_handle_t cpuid_handle_t;

int hdc_cpuid_init(cpuid_handle_t** handle);

int hdc_cpuid_vendor_type(cpuid_handle_t* handle);

const char* hdc_cpuid_identify(cpuid_handle_t* handle);

void hdc_cpuid_destroy(cpuid_handle_t* handle);

#endif
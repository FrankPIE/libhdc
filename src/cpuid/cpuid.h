/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_H_
#define _HDC_CPUID_H_

typedef struct _cpuid_handle_t cpuid_handle_t;

typedef enum _CPUVendor
{
	CPU_UNKNOWN,
	CPU_INTEL,
	CPU_AMD,
	CPU_ARM
} CPUVendor;

int hdc_cpuid_init(cpuid_handle_t** handle);

void hdc_cpuid_destroy(cpuid_handle_t* handle);

#endif
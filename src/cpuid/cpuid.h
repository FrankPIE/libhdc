/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_H_
#define _HDC_CPUID_H_

#include <stdbool.h>
#include <common/uuid.h>

typedef struct _cpuid_handle_t cpuid_handle_t;

int  hdc_cpuid_init(cpuid_handle_t** handle);

int  hdc_cpuid_vendor_type(cpuid_handle_t* handle);

int  hdc_cpuid_serial_number(cpuid_handle_t* handle, hdc_uuid_t* uuid);

bool hdc_cpuid_serial_number_support(cpuid_handle_t* handle);

const char* hdc_cpuid_identify(cpuid_handle_t* handle);

void hdc_cpuid_destroy(cpuid_handle_t* handle);

#endif
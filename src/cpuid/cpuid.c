/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <cpuid/cpuid.h>

#include <assert.h>
#include <stdlib.h>

#include <stdbool.h>

/* ***********************interface*********************** */

extern cpuid_handle_t* cpuid_handle_init();
extern bool			   cpuid_handle_cpuid_support(cpuid_handle_t* handle);
extern int			   cpuid_handle_vendor_type(cpuid_handle_t* handle);
extern void			   cpuid_handle_destroy(cpuid_handle_t* handle);

extern char*		   cpuid_identify_string(cpuid_handle_t* handle);

/* ***********************implement*********************** */

int hdc_cpuid_init(cpuid_handle_t** handle)
{
	assert(*handle == NULL);

	*handle = cpuid_handle_init();

	if (!(*handle))
		return 0;

	if (!cpuid_handle_cpuid_support(*handle))
		return 0;

	return 1;
}

int hdc_cpuid_vendor_type(cpuid_handle_t* handle)
{
	assert(cpuid_handle_cpuid_support(handle));

	return cpuid_handle_vendor_type(handle);
}

const char* hdc_cpuid_identify(cpuid_handle_t* handle)
{
	assert(cpuid_handle_cpuid_support(handle));

	return cpuid_identify_string(handle);
}

void hdc_cpuid_destroy(cpuid_handle_t* handle)
{
	cpuid_handle_destroy(handle);
}

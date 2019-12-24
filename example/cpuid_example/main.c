/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdio.h>

#include <cpuid/cpuid.h>

int main(int argc, char* argv[])
{
	cpuid_handle_t* handle = NULL;

	hdc_cpuid_init(&handle);

	printf("identify : %s", hdc_cpuid_identify(handle));
	
	hdc_cpuid_destroy(handle);
}

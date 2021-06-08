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
	hdc_uuid_t uuid;

	hdc_cpuid_init(&handle);

	printf("CPU Identify : %s\n", hdc_cpuid_cpu_identify(handle));
	printf("Processor Type : %s\n", hdc_cpuid_processor_type(handle));
	printf("Processor Family : %x\n", hdc_cpuid_cpu_family(handle));
	printf("Processor Model : %x\n", hdc_cpuid_cpu_model(handle));
	printf("Processor Stepping : %x\n", hdc_cpuid_cpu_stepping(handle));
	printf("Processor Extended Family : %x\n", hdc_cpuid_cpu_extended_family(handle));
	printf("Processor Extended Model : %x\n", hdc_cpuid_cpu_extended_model(handle));

	if (hdc_cpuid_cpu_psn_support(handle))
	{
		hdc_cpuid_cpu_serial_number(handle, &uuid);

		printf("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x%02x%02x\n",
			uuid.uuid[0], uuid.uuid[1], uuid.uuid[2], uuid.uuid[3],
			uuid.uuid[4], uuid.uuid[5],
			uuid.uuid[6], uuid.uuid[7],
			uuid.uuid[8], uuid.uuid[9], uuid.uuid[10], uuid.uuid[11], uuid.uuid[12], uuid.uuid[13], uuid.uuid[14], uuid.uuid[15]
		);
	}

	
	hdc_cpuid_destroy(handle);
}

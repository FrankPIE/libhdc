/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdio.h>

#include <hdc.h>

int main(int argc, char* argv[])
{
	hdc_handle_t* handle;

	hdc_init(&handle);

	const char* manufacturer = NULL;
	hdc_baseboard_manufacturer(handle, &manufacturer);
	const char* product = NULL;
	hdc_baseboard_product(handle, &product);

	printf("baseboard : %s %s \n", manufacturer, product);

	unsigned char uuid[16];
	hdc_system_uuid(handle, uuid);

	printf("system uuid : %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
		uuid[0], uuid[1], uuid[2], uuid[3],
		uuid[4], uuid[5],
		uuid[6], uuid[7],
		uuid[8], uuid[9], 
		uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
	);

	const char* bios_vendor = NULL;
	hdc_bios_vendor(handle, &bios_vendor);

	const char* bios_version = NULL;
	hdc_bios_version(handle, &bios_version);

	const char* bios_release_date = NULL;
	hdc_bios_release_date(handle, &bios_release_date);

	printf("bios : %s %s %s \n", bios_vendor, bios_version, bios_release_date);

	hdc_destroy(handle);
	
	return 0;
}

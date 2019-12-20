/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdio.h>

#include <smbios/smbios_table.h>

int main(int argc, char* argv[])
{
	hdc_smbios_table_data_t* data;

	hdc_smbios_init(&data);
	
	printf("Base Board : %s ", hdc_smbios_baseboard_manufacturer(data));
	printf("%s\n", hdc_smbios_baseboard_product(data));

	hdc_uuid_t uuid;

	hdc_smbios_system_uuid(data, &uuid);

	printf("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x%02x%02x\n",
		uuid.uuid[0], uuid.uuid[1], uuid.uuid[2], uuid.uuid[3],
		uuid.uuid[4], uuid.uuid[5],
		uuid.uuid[6], uuid.uuid[7],
		uuid.uuid[8], uuid.uuid[9], uuid.uuid[10], uuid.uuid[11], uuid.uuid[12], uuid.uuid[13], uuid.uuid[14], uuid.uuid[15]
	);

	printf("BIOS : %s ", hdc_smbios_bios_vendor(data));
	printf("%s\n", hdc_smbios_bios_version(data));
	printf("Release Date : %s\n", hdc_smbios_bios_release_date(data));

	hdc_smbios_destroy(data);
	
	return 0;
}

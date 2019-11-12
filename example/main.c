/*
* Copyright (C) 2019 MadStrawberry
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial 
* portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/
#include <stdio.h>

#include <SMBIOSTable.h>

int main(int argc, char* argv[])
{
	SMBIOSTableData* data;

	hdc_smbios_init(&data);

	printf("Base Board : %s ", hdc_smbios_baseboard_manufacturer(data));
	printf("%s\n", hdc_smbios_baseboard_product(data));

	SMBIOS_UUID uuid;

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

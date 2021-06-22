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
	
	unsigned char uuid[16];
	hdc_system_uuid(handle, uuid);

	printf("%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n",
		uuid[0], uuid[1], uuid[2], uuid[3],
		uuid[4], uuid[5],
		uuid[6], uuid[7],
		uuid[8], uuid[9], 
		uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
	);

	hdc_destroy(handle);
	
	return 0;
}

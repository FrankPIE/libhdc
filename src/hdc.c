/*
* Copyright (C) 2021 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <hdc.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <common/errorc.h>
#include <smbios/smbios_table.h>

struct _hdc_handle_t
{
	hdc_smbios_table_data_t* smbios_table;
};

int LIBHDC_CALL hdc_init(hdc_handle_t** handle)
{
	*handle = (hdc_handle_t*)malloc(sizeof(struct _hdc_handle_t));

	if (*handle)
	{
		error_map_init();
		
		if (hdc_smbios_init(&(*handle)->smbios_table) == 1)
		{
			return HDC_SUCCESS;
		}
	}
	
	return HDC_EC_BAD_ALLOC;
}

int LIBHDC_CALL hdc_system_uuid(hdc_handle_t* handle, unsigned char uuid[16])
{
	assert(handle != NULL && handle->smbios_table);

	hdc_uuid_t uuid_value;
	if (hdc_smbios_system_uuid(handle->smbios_table, &uuid_value))
	{
		memcpy(uuid, uuid_value.uuid, 16);

		return HDC_SUCCESS;
	}
	
	return HDC_SUCCESS;
}

const char* LIBHDC_CALL hdc_error_message(int errorc)
{
	return error_information(errorc);
}

int LIBHDC_CALL hdc_destroy(hdc_handle_t* handle)
{
	if (handle)
	{
		if (handle->smbios_table)
		{
			hdc_smbios_destroy(handle->smbios_table);
		}

		error_map_destroy();
		
		free(handle);
	}
	
	return HDC_SUCCESS;
}

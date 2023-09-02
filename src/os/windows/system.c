/*
* Copyright (C) 2023 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <os/system.h>

#include <assert.h>
#include <common/errorc.h>

#include <Windows.h>

struct _os_handle_t
{
	SYSTEM_INFO win_os_info;
};

int os_init(os_handle_t** handle)
{
	assert(*handle == NULL);

	*handle = (os_handle_t*)malloc(sizeof(struct _os_handle_t));

	if (*handle == NULL)
		return HDC_EC_BAD_ALLOC;

	GetSystemInfo(&((*handle)->win_os_info));

	return HDC_SUCCESS;
}

int os_cpu_logical_cores(os_handle_t* handle)
{
	assert(handle != NULL);

	return (int)handle->win_os_info.dwNumberOfProcessors;
}

int os_destory(os_handle_t* handle)
{
	if (handle) {
		free(handle);
	}

	return HDC_SUCCESS;
}

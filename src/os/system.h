/*
* Copyright (C) 2023 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_SYSTEM_H_
#define _HDC_SYSTEM_H_

typedef struct _os_handle_t os_handle_t;

int os_init(os_handle_t** handle);

int os_cpu_logical_cores(os_handle_t* handle);

int os_destory(os_handle_t* handle);

#endif

/*
* Copyright (C) 2021 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_H_
#define _HDC_H_

#ifdef libhdc_EXPORTS
#define LIBHDC_API _declspec(dllexport)
#else
#define LIBHDC_API _declspec(dllimport)
#endif

#define LIBHDC_CALL __stdcall

typedef struct _hdc_handle_t hdc_handle_t;

LIBHDC_API int LIBHDC_CALL hdc_init(hdc_handle_t** handle);

LIBHDC_API int LIBHDC_CALL hdc_system_uuid(hdc_handle_t* handle, unsigned char uuid[16]);

LIBHDC_API const char* LIBHDC_CALL hdc_error_message(int errorc);

LIBHDC_API int LIBHDC_CALL hdc_destroy(hdc_handle_t* handle);

#endif

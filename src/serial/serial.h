/*
* Copyright (C) 2021 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_SERIAL_H_
#define _HDC_SERIAL_H_

#include <stddef.h>
#include <hdc_type.h>

typedef struct _serial_handle_t serial_handle_t;

int serial_device_open(serial_handle_t** handle, const char* serial_device);

int serial_device_set(serial_handle_t* handle, hdc_serial_device_property property, const void* value);

int serial_device_get(serial_handle_t* handle, hdc_serial_device_property property, void* value);

int serial_device_send(serial_handle_t* handle, const void* data, size_t size, size_t* send_size);

int serial_device_receive(serial_handle_t* handle, void* buffer, size_t buffer_size, size_t* receive_size);

void serial_device_close(serial_handle_t* handle);

#endif


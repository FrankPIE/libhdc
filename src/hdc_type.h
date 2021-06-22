/*
* Copyright (C) 2021 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_TYPE_H_
#define _HDC_TYPE_H_

typedef struct _hdc_handle_t hdc_handle_t;

typedef enum _hdc_serial_device_property
{
	SERIAL_DEVICE_BAUD,
	SERIAL_DEVICE_DATABITS,
	SERIAL_DEVICE_STOPBITS,
	SERIAL_DEVICE_PARITY,
	SERIAL_DEVICE_DTR,
	SERIAL_DEVICE_RTS
} hdc_serial_device_property;

#endif


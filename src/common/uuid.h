/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_UUID_H_
#define _HDC_UUID_H_

#include <stdint.h>

typedef struct _hdc_uuid_t
{
	uint8_t uuid[16];
} hdc_uuid_t;

#endif
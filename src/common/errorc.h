/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_ERROR_CODE_H_
#define _HDC_ERROR_CODE_H_

#define HDC_SUCCESS										  0
#define HDC_EC_BAD_ALLOC								(-1)
#define HDC_EC_CPUID_NOT_SUPPORT						(-2)
#define HDC_EC_CPUID_SERIAL_NUMBER_NOT_SUPPORT			(-3)
#define HDC_EC_ERROR_PARAMETER							(-4)
#define HDC_EC_TOO_OLD_CPU_PRODUCT						(-5)
#define HDC_EC_UNDEFINED								(-6)

void error_map_init();

const char* error_information(int error_code);

void error_map_destroy();

#endif

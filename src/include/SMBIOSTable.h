/*
* Copyright (C) 2019 MadStrawberry
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* ¡¡¡¡
* The above copyright notice and this permission notice shall be included in all copies or substantial 
* portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#ifndef _HDC_SMBIOS_TABLE_H_
#define _HDC_SMBIOS_TABLE_H_

#include <stdint.h>

#include <HDCConfig.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct _hdc_smbios_table_data_t hdc_smbios_table_data_t;

typedef struct _smbios_uuid_t
{
	uint8_t uuid[16];
} smbios_uuid_t;

/**
 * \brief 
 * \param table_data 
 * \return 
 */
int HDC_CALLBACK_API  hdc_smbios_init(hdc_smbios_table_data_t** table_data);

/**
 * \brief 
 * \param table_data 
 * \return 
 */
const char* HDC_CALLBACK_API hdc_smbios_bios_vendor(hdc_smbios_table_data_t* table_data);

/**
 * \brief 
 * \param table_data 
 * \return 
 */
const char* HDC_CALLBACK_API hdc_smbios_bios_version(hdc_smbios_table_data_t* table_data);

/**
 * \brief 
 * \param table_data 
 * \return 
 */
const char* HDC_CALLBACK_API hdc_smbios_bios_release_date(hdc_smbios_table_data_t* table_data);

/**
 * \brief 
 * \param table_data 
 * \param uuid 
 * \return 
 */
int HDC_CALLBACK_API hdc_smbios_system_uuid(hdc_smbios_table_data_t* table_data, smbios_uuid_t* uuid);

/**
 * \brief 
 * \param table_data 
 * \return 
 */
const char* HDC_CALLBACK_API hdc_smbios_baseboard_manufacturer(hdc_smbios_table_data_t* table_data);

/**
 * \brief 
 * \param table_data 
 * \return 
 */
const char* HDC_CALLBACK_API hdc_smbios_baseboard_product(hdc_smbios_table_data_t* table_data);

/**
 * \brief 
 * \param table_data 
 */
void HDC_CALLBACK_API hdc_smbios_destroy(hdc_smbios_table_data_t* table_data);

#if defined(__cplusplus)
}
#endif

#endif 
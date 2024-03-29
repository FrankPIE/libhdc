/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdlib.h>

#include <common/errorc.h>
#include <common/hashmap.h>

static hash_map_t* kErrorCodeMap = NULL;

void error_map_destroy()
{
	hash_map_destroy(kErrorCodeMap);
}

void error_map_init()
{
#define MakeErrorCodeDecrement (--error_code, sizeof(int))

	int error_code = HDC_SUCCESS;
	
	if (kErrorCodeMap != NULL)
		return;

	hash_map_item_t table[] =
	{
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("execute success")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("bad alloc memory")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("no cpuid instruct support")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("no cpuid serial number support")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("function call with error parameter")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("too old cpu product to support")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("undefined error")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("create device handle failed")),
		make_pair(make_buffer_key((unsigned char*)&error_code, MakeErrorCodeDecrement), make_string_value("invalid device handle"))		
	};

	hash_map_init(&kErrorCodeMap, table, sizeof(table) / sizeof(hash_map_item_t));

#undef MakeErrorCodeDecrement
}

const char* error_information(int error_code)
{
	char* value = NULL;
	
	if (kErrorCodeMap)
		hash_map_find(kErrorCodeMap, make_buffer_key((unsigned char*)&error_code, sizeof(int)), (void**)&value);

	return value;
}
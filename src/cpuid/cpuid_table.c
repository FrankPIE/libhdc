/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdlib.h>

#include <common/hashmap.h>

#include <cpuid/cpuid.h>

#define HASH_MAP_INIT(hash_map, table) \
	hash_map_init(&(hash_map), (table), sizeof(table) / sizeof(hash_map_item_t))

extern hash_map_t* cpuid_vendor_table();

extern hash_map_t* intel_cpuid_brand_id_table();

hash_map_t* cpuid_vendor_table()
{
	hash_map_t* hash_map = NULL;

	const int intel_flag = HDC_CPU_VENDOR_INTEL;
	const int amd_flag = HDC_CPU_VENDOR_AMD;

	hash_map_item_t table[] = 
	{
		make_pair(make_string_key("GenuineIntel"), make_buffer_value((void*)&intel_flag, sizeof(int))),
		make_pair(make_string_key("AuthenticAMD"), make_buffer_value((void*)&amd_flag, sizeof(int))),
	};

	HASH_MAP_INIT(hash_map, table);
	
	return hash_map;
}

hash_map_t* intel_cpuid_brand_id_table()
{
#define MakeIndexIncrement (++index, sizeof(int))
	hash_map_t* hash_map = NULL;

	int index = 0x01;
	
	hash_map_item_t table[] =
	{
		//index == 01h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		//index == 02h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III processor")),

		//index == 03h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III Xeon(R) processor")),

		//index == 04h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III processor")),

		// index == 05h, equal index == 03h and signature = 0x06B1
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 06h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Pentium(R) III processor-M")),

		// index == 07h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 08h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) 4 processor")),

		// index == 09h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) 4 processor")),

		// index == 0Ah
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 0Bh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor")),

		// index == 0Ch
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor MP")),

		// index == 0Dh, equal index == 0Bh and signature = 0x0F13
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor MP")),

		// index == 0Eh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Pentium(R) 4 processor-M")),

		// index == 0Fh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 10h, equal index == 0Eh and signature = 0x0F13
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor")),

		// index == 11h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Genuine Intel(R) processor")),

		// index == 12h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron M processor")),

		// index == 13h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 14h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 15h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Genuine Intel(R) processor")),

		// index == 16h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) M processor")),

		// index == 17h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),
	};

	HASH_MAP_INIT(hash_map, table);
	
#undef MakeIndexIncrement
	return hash_map;
}

#undef HASH_MAP_INIT
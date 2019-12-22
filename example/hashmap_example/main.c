/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdio.h>
#include <stdlib.h>

#include <common/hashmap.h>

int main(int argc, char* argv[])
{
	hash_map_t* hash_map = NULL;

	hash_map_item_t table[] = 
	{
		make_pair(make_string_key("hello world!"), make_string_value("Hello World!")),
		make_pair(make_string_key("hello world?"), make_string_value("Hello World?")),
		make_pair(make_string_key("hello world#"), make_string_value("Hello World#"))
	};
	
	hash_map_init(&hash_map, table, sizeof(table) / sizeof(hash_map_item_t));

	key_t key = make_string_key("hello world!");

	char* value = NULL;
	
	hash_map_find(hash_map, key, (void**)(&value));

	printf("find string %s", value);
	
	hash_map_destroy(hash_map);
}

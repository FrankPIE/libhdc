/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/
#include <stddef.h>

#include <common/hashmap.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	hash_map_t* hash_map = NULL;

	hash_map_item_t* table = (hash_map_item_t*)malloc(sizeof(hash_map_item_t) * 2);

	if (table)
	{
		table[0].key = make_string_key("hello world!");
		table[0].value = make_string_value("Hello World!");

		table[1].key = make_string_key("hello world?");
		table[1].value = make_string_value("Hello World?");
	}
	
	hash_map_init(&hash_map, table, 2);

	key_t key = make_string_key("hello world!");

	char* value = NULL;
	
	hash_map_find(hash_map, key, (void**)(&value));
	
	hash_map_destroy(hash_map);

	free(table);
}

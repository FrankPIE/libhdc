/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_HASH_MAP_H_
#define _HDC_HASH_MAP_H_

typedef struct _key_t
{
	unsigned char* buffer;
	unsigned int   buffer_size;
} key_t;

typedef void* value_t;

typedef struct _hash_map_item_t
{
	key_t	key;
	value_t value;
} hash_map_item_t;

typedef struct _hash_map_t hash_map_t;

key_t make_buffer_key(unsigned char* buffer, unsigned int size);

key_t make_string_key(const char* string);

value_t make_buffer_value(void* buffer, unsigned int size);

value_t make_string_value(const char* string);

int hash_map_init(hash_map_t** hash_map, hash_map_item_t* items, unsigned int size);

int hash_map_find(hash_map_t* hash_map, key_t key, value_t* value);

void hash_map_destroy(hash_map_t* hash_map);


#endif

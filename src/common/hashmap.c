/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include <common/hashmap.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define UNIVERSAL_HASH_P 49999ui32
 
/* hash map use perfect hashing */

extern uint32_t crc32(const unsigned char* buf, unsigned int size);

/* universal hash function expression h(k) = ((a*k + b) mod p) mod m */
static uint32_t hash_function(uint32_t hash, uint32_t m, uint32_t a, uint32_t b)
{
	return ((a * hash + b) % UNIVERSAL_HASH_P) % m;
}

static uint32_t hash_alpha()
{
	return rand() % UNIVERSAL_HASH_P;
}

static uint32_t hash_beta()
{
	return rand() % (UNIVERSAL_HASH_P - 1) + 1;
}

struct _hash_map_t
{
	uint32_t  alpha, beta;
	uint32_t  size;

	struct _hash_list_t
	{
		uint32_t  alpha, beta;
		uint32_t  size;

		struct _hash_item_t
		{
			uint32_t  hash;
			value_t   value;
		} *items;
	} **list;
};

struct _hash_map_helper_t
{
	uint32_t hash;
	uint32_t counter;

	uint32_t hash_index;
};

key_t make_buffer_key(unsigned char* buffer, unsigned int size)
{
	const key_t key = { buffer, size };
	
	return key;
}

key_t make_string_key(const char* string)
{
	return make_buffer_key((unsigned char*)string, strlen(string));
}

value_t make_buffer_value(void* buffer, unsigned int size)
{
	void* memory = malloc(size);

	if (memory)
	{
		memcpy(memory, buffer, size);
	}

	return memory;
}

value_t make_string_value(const char* string)
{
	const size_t size = sizeof(char) * strlen(string);
	
	char* memory = (char*)malloc(size + 1);

	if (memory)
	{
		memcpy((void*)memory, string, size);
		memset(memory + size, '\0', 1);
	}
	
	return memory;
}

hash_map_item_t make_pair(key_t key, value_t value)
{
	const hash_map_item_t item = { key, value };

	return item;
}

static void* make_array(uint32_t type_size, uint32_t array_size)
{
	const uint32_t size = type_size * array_size;
	
	void* array = malloc(size);

	if (!array)
		return NULL;

	memset(array, 0, size);

	return array;	
}

static void hash(struct _hash_list_t* list, uint32_t list_index, struct _hash_map_helper_t* helper, hash_map_item_t* items, uint32_t size)
{
	bool success = false;
	
	do
	{		
		uint32_t index = 0;

		list->alpha = hash_alpha();
		list->beta = hash_beta();

		for (index = 0; index < size; ++index)
		{
			if (helper[index].hash_index == list_index)
			{				
				const uint32_t position = hash_function(helper[index].hash, list->size, list->alpha, list->beta);

				assert(list->items[position].hash != helper[index].hash);

				list->items[position].hash = helper[index].hash;

				if (list->items[position].value != NULL)
					continue;
				
				list->items[position].value = items[index].value;
			}
		}

		success = true;
	}
	while (!success);
}

int hash_map_init(hash_map_t** hash_map, hash_map_item_t* items, unsigned int size)
{	
	unsigned int index = 0;

	struct _hash_map_helper_t* helper = (struct _hash_map_helper_t*)make_array(sizeof(struct _hash_map_helper_t), size);

	if (!helper)
		return 0;

	srand((unsigned)time(NULL));

	*hash_map = (hash_map_t*)malloc(sizeof(hash_map_t));

	if (*hash_map == NULL)
		return 0;

	(*hash_map)->alpha = hash_alpha();
	(*hash_map)->beta = hash_beta();
	(*hash_map)->size = size;

	(*hash_map)->list = (struct _hash_list_t**)make_array(sizeof(struct _hash_list_t*), size);
	
	for (index = 0; index < size; ++index)
	{
		uint32_t position;

		helper[index].hash = crc32(items[index].key.buffer, items[index].key.buffer_size);

		position = hash_function(helper[index].hash, (*hash_map)->size, (*hash_map)->alpha, (*hash_map)->beta);

		++helper[position].counter;

		helper[index].hash_index = position;
	}

	for (index = 0; index < size; ++index)
	{
		if (helper[index].counter > 0)
		{			
			(*hash_map)->list[index] = (struct _hash_list_t*)malloc(sizeof(struct _hash_list_t));

			if ((*hash_map)->list[index])
			{
				(*hash_map)->list[index]->size = helper[index].counter * helper[index].counter;

				(*hash_map)->list[index]->items = (struct _hash_item_t*)make_array(sizeof(struct _hash_item_t), (*hash_map)->list[index]->size);
			}
		}
	}

	for (index = 0; index < size; ++index)
	{
		if ((*hash_map)->list[index] != NULL)
		{
			hash((*hash_map)->list[index], index, helper, items, size);
		}				
	}
	
	if (helper)
		free(helper);

	return 1;
}

int hash_map_find(hash_map_t* hash_map, key_t key, value_t* value)
{
	const uint32_t hash = crc32(key.buffer, key.buffer_size);

	uint32_t index = hash_function(hash, hash_map->size, hash_map->alpha, hash_map->beta);

	struct _hash_list_t* list = hash_map->list[index];

	if (!list)
		return 0;
	
	index = hash_function(hash, list->size, list->alpha, list->beta);

	*value = list->items[index].value;

	if (*value == NULL)
		return 0;
	
	return 1;
}

void hash_map_destroy(hash_map_t* hash_map)
{
	unsigned int index = 0;
	unsigned int iterator = 0;

	if (hash_map)
	{
		for (index = 0; index < hash_map->size; ++index)
		{
			struct _hash_list_t* list = hash_map->list[index];

			if (list)
			{
				struct _hash_item_t* items = hash_map->list[index]->items;

				if (items)
				{
					for (iterator = 0; iterator < list->size; ++iterator)
					{
						if (items[iterator].value)
							free(hash_map->list[index]->items[iterator].value);
					}
	
					free(items);
				}

				free(list);
			}
		}

		free(hash_map);
	}
}
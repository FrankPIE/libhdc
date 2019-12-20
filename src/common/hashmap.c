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
			value_t   value;
		} *items;
	} **list;
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

int hash_map_init(hash_map_t** hash_map, hash_map_item_t* items, unsigned int size)
{	
	unsigned int index = 0;

	srand((unsigned)time(NULL));

	*hash_map = (hash_map_t*)malloc(sizeof(hash_map_t));

	if (*hash_map == NULL)
		return 0;

	(*hash_map)->alpha = hash_alpha();
	(*hash_map)->beta = hash_beta();
	(*hash_map)->size = size;

	(*hash_map)->list = (struct _hash_list_t**)malloc(sizeof(struct _hash_list_t*) * size);

	memset((*hash_map)->list, 0, sizeof(struct _hash_list_t*) * size);

	int* counter = (int*)malloc(sizeof(int) * size);

	memset(counter, 0, sizeof(int) * size);

	uint32_t *hash_value = (unsigned int*)malloc(sizeof(uint32_t) * size);

	memset(hash_value, 0, sizeof(uint32_t) * size);

	if (!hash_value)
		return 0;

	for (index = 0; index < size; ++index)
	{
		uint32_t position;

		hash_value[index] = crc32(items[index].key.buffer, items[index].key.buffer_size);

		position = hash_function(hash_value[index], (*hash_map)->size, (*hash_map)->alpha, (*hash_map)->beta);

		++counter[position];
	}

	for (index = 0; index < size; ++index)
	{		
		uint32_t position;

		if (counter[index] > 0)
		{
			(*hash_map)->list[index] = (struct _hash_list_t*)malloc(sizeof(struct _hash_list_t));

			(*hash_map)->list[index]->alpha = hash_alpha();
			(*hash_map)->list[index]->beta = hash_beta();
			(*hash_map)->list[index]->size = counter[index] * counter[index];

			(*hash_map)->list[index]->items = (struct _hash_item_t*)malloc(sizeof(struct _hash_item_t) * (*hash_map)->list[index]->size);

			memset((*hash_map)->list[index]->items, 0, sizeof(struct _hash_item_t) * (*hash_map)->list[index]->size);

			position = hash_function(hash_value[index], (*hash_map)->list[index]->size, (*hash_map)->list[index]->alpha, (*hash_map)->list[index]->beta);

			(*hash_map)->list[index]->items[position].value = items[index].value;
		}
	}

	if (counter)
		free(counter);

	if (hash_value)
		free(hash_value);

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
#pragma once

#ifndef DRT_REREF_CACHE_HASHMAP_H
#define DRT_REREF_CACHE_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

#include "../key/key.h"
#include "hashmap_entry.h"


typedef struct HashMapComparators {
	KeyComparator getComparator;
	KeyComparator insertComparator;
	KeyComparator deleteComparator;
} HashMapComparators;

typedef struct HashMap {
	size_t size;
	size_t count;
	HashMapComparators comparators;
	KeyHandlers handlers;
	HashMapEntry** entries;
} HashMap;

HashMap* hm_create(AM_ALLOCATOR_PARAM size_t size, HashMapComparators comparators, KeyHandlers handlers);
void hm_destroy(AM_ALLOCATOR_PARAM HashMap* hm);
int hm_resize(AM_ALLOCATOR_PARAM HashMap* hm);

HashMapEntry* hm_get(HashMap* hm, const char* key);
int ht_insert(AM_ALLOCATOR_PARAM
			  HashMap* hm,
			  const char* key,
			  void* value,
			  HashMapEntry** entryAtIndex,
			  void** overridden);

void* hm_delete_entry(AM_ALLOCATOR_PARAM HashMap* hm, size_t index);
void* hm_delete(AM_ALLOCATOR_PARAM HashMap* hm, const char* key);

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_HASHMAP_H

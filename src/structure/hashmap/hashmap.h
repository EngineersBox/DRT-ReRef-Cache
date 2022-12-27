#pragma once

#ifndef DRT_REREF_CACHE_HASHMAP_H
#define DRT_REREF_CACHE_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

#include "hashmap_entry.h"

typedef int (*KeyComaprator)(const char* key1, const char* key2, void* key2Value);

typedef struct HashMapComparators {
	KeyComaprator getComparator;
	KeyComaprator putComparator;
	KeyComaprator deleteComparator;
} HashMapComparators;

typedef struct HashMap {
	size_t size;
	size_t count;
	HashMapComparators comparators;
	HashMapEntry** entries;
} HashMap;

HashMap* hm_create(AM_ALLOCATOR_PARAM size_t size, HashMapComparators comparators);
void hm_destroy(AM_ALLOCATOR_PARAM HashMap* hm);
int hm_resize(AM_ALLOCATOR_PARAM HashMap* hm);

HashMapEntry* hm_get(HashMap* hm, const char* key);
int ht_insert(AM_ALLOCATOR_PARAM HashMap* hm, const char* key, void* value, HashMapEntry** entryAtIndex, void** overridden);

void* hm_delete_entry(AM_ALLOCATOR_PARAM HashMap* hm, size_t index);
void* hm_delete(AM_ALLOCATOR_PARAM HashMap* hm, const char* key);

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_HASHMAP_H

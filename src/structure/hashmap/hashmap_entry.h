#pragma once

#ifndef DRT_REREF_CACHE_HASHMAP_ENTRY_H
#define DRT_REREF_CACHE_HASHMAP_ENTRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "../../allocator/alloc_manager.h"
#include "../key/key.h"

typedef struct HashMapEntry {
	size_t keyLength;
	size_t index;
	const char* key;
	void* value;
	struct HashMapEntry* prev;
	struct HashMapEntry* next;
} HashMapEntry;

HashMapEntry* hme_create(AM_ALLOCATOR_PARAM const char* key, void* value);
HashMapEntry* hme_create_full(AM_ALLOCATOR_PARAM
							  const char* key,
							  void* value,
							  KeyHandlers keyHandlers,
							  HashMapEntry* prev,
							  HashMapEntry* next);
void hme_destroy(AM_ALLOCATOR_PARAM HashMapEntry* entry);

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_HASHMAP_ENTRY_H

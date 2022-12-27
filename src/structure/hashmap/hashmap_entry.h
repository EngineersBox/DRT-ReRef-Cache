#pragma once

#ifndef DRT_REREF_CACHE_HASHMAP_ENTRY_H
#define DRT_REREF_CACHE_HASHMAP_ENTRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "../../allocator/alloc_manager.h"

typedef struct HashMapEntry {
	size_t keyLength;
	size_t index;
	const char* key;
	void* value;
	struct HashMapEntry* prev;
	struct HashMapEntry* next;
} HashMapEntry;

typedef size_t (*KeySize)(const char*);
typedef char* (*KeyClone)(AM_ALLOCATOR_PARAM const char*, KeySize);

typedef struct HashMapEntryKeyHandlers {
	KeySize keySize;
	KeyClone keyClone;
} HashMapEntryKeyHandlers;

HashMapEntry* hme_create(AM_ALLOCATOR_PARAM const char* key, void* value);
HashMapEntry* hme_create_full(AM_ALLOCATOR_PARAM const char* key, void* value, HashMapEntryKeyHandlers keyHandlers, HashMapEntry* prev, HashMapEntry* next);
void hme_destroy(AM_ALLOCATOR_PARAM HashMapEntry* entry);

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_HASHMAP_ENTRY_H

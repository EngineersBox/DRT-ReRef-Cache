#pragma once

#ifndef DRT_REREF_CACHE_DEQUEUE_HASHMAP_H
#define DRT_REREF_CACHE_DEQUEUE_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../key/key.h"
#include "../hashmap/hashmap.h"

typedef struct DequeueHashMap {
	HashMapEntry* head;
	HashMapEntry* tail;
	HashMap* hm;	
} DequeueHashMap;

DequeueHashMap* dqhm_create(AM_ALLOCATOR_PARAM size_t size, HashMapComparators comparators, KeyHandlers handlers);
void dqhm_destroy(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm);

void* dqhm_get(DequeueHashMap* dqhm, const char* key);
// -1: Failure, 0: No entry, 1: Matching entry
int dqh_delete(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm, const char* key, void** removed);

void* dqhm_get_front(DequeueHashMap* dqhm);
int dqhm_push_front(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm, const char* key, void* value);
void* dqht_pop_front(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm, const char* key, void** removed);

void* dqhm_get_last(DequeueHashMap* dqhm);
int dqhm_push_last(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm, const char* key, void* value);
void* dqhm_pop_last(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm, const char* key, void** removed);

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_DEQUEUE_HASHMAP_H

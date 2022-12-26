#pragma once

#ifndef DRT_REREF_CACHE_HASHMAP_H
#define DRT_REREF_CACHE_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

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
} HashMap;

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_HASHMAP_H

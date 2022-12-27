
#pragma once

#ifndef DRT_REREF_CACHE_KEY_H
#define DRT_REREF_CACHE_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "../../allocator/alloc_manager.h"

typedef int (*KeyComparator)(const char* key1, const char* key2, void* key2Value);

typedef size_t (*KeySize)(const char*);
typedef char* (*KeyClone)(AM_ALLOCATOR_PARAM const char*, KeySize);

typedef struct KeyHandlers {
	KeySize keySize;
	KeyClone keyClone;
} KeyHandlers;


#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_KEY_H

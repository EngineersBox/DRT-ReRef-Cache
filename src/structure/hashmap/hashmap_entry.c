#include "hashmap_entry.h"

#include <string.h>
#include "../../utils/check.h"

size_t default_key_size(const char* key) {
	return strlen(key);
}

char* default_key_clone(AM_ALLOCATOR_ARG
						const char* key,
						KeySize keySizeFunc) {
	size_t keySize = keySizeFunc(key);
	char* newKey = (char*) am_calloc(sizeof(*newKey), keySize);
	NULL_CHECK_RET_NULL(newKey);
	memcpy(newKey, key, keySize);
	return newKey;
}

HashMapEntry* hme_create(AM_ALLOCATOR_PARAM const char* key, void* value) {
	return hme_create_full(
			AM_ALLOCATOR_ARG
			key,
			value,
			(HashMapEntryKeyHandlers) {
				.keySize = default_key_size,
				.keyClone = default_key_clone
			},
			NULL,
			NULL
	);
}

HashMapEntry* hme_create_full(AM_ALLOCATOR_PARAM
							  const char* key,
							  void* value,
							  HashMapEntryKeyHandlers keyHandlers,
							  HashMapEntry* prev,
							  HashMapEntry* next) {
	HashMapEntry* entry  = (HashMapEntry*) am_malloc(sizeof(*entry));
	NULL_CHECK_RET_NULL(entry);
	entry->keyLength = keyHandlers.keySize(key);
	entry->key = keyHandlers.keyClone(AM_ALLOCATOR_ARG key, keyHandlers.keySize);
	NULL_CHECK_RET_NULL(entry->key);
	entry->value = value;
	entry->prev = prev;
	entry->next = next;
	entry->index = 0;
	return entry;
}

void hme_destroy(AM_ALLOCATOR_PARAM HashMapEntry* entry) {
	NULL_CHECK_RET_NONE(entry);
	NULL_CHECK_RET_NONE(entry->key);
	am_free((void*) entry->key);
	entry->key = NULL;
	entry->next = NULL;
	entry->prev = NULL;
	entry->index = 0;
	am_free(entry);
}

#include "hashmap.h"

#include "../../utils/check.h"
#include "hashing.h"

HashMap* hm_create(AM_ALLOCATOR_PARAM size_t size, HashMapComparators comparators, KeyHandlers handlers) {
	HashMap* map = (HashMap*) am_malloc(sizeof(*map));
	NULL_CHECK_RET_NULL(map);
	map->size = size;
	map->count = 0;
	map->comparators = comparators;
	map->handlers = handlers;
	map->entries = (HashMapEntry**) am_calloc(sizeof(HashMapEntry*), size);
	NULL_CHECK_RET_NULL(map->entries);
	return map;
}

void hm_destroy(AM_ALLOCATOR_PARAM HashMap* hm) {
	NULL_CHECK_RET_NONE(hm);
	NULL_CHECK_RET_NONE(hm->entries);
	for (int i = 0; i < hm->size; i++) {
		if (hm->entries[i] == NULL) continue;
		hme_destroy(AM_ALLOCATOR_ARG hm->entries[i]);
	}
	am_free(hm->entries);
	am_free(hm);
}

int hm_insert(AM_ALLOCATOR_PARAM
			  HashMap* hm,
			  const char* key,
			  void* value,
			  HashMapEntry** entryAtIndex,
			  void** overridden) {
	NULL_CHECK_RET_VAL(hm, -1);
	NULL_CHECK_RET_VAL(hm->entries, -1);
	NULL_CHECK_RET_VAL(key, -1);
	NULL_CHECK_RET_VAL(value, -1);
	if (hm->count >= (hm->size / 2)) {
		if (hm_resize(AM_ALLOCATOR_ARG hm) != 0) {
			return -1;
		}
	}
	size_t hash = HASH_FUNC(key, hm->handlers.keySize);
	size_t index = hash % hm->size;
	for (int i = 0; i < hm->size && hm->entries[index] != NULL; i++) {
		if (hm->entries[index]->key != NULL
			&& hm->comparators.insertComparator(key, hm->entries[index]->key, hm->entries[index]->value) == 0) {
			if (overridden != NULL) {
				*overridden = hm->entries[index]->value;
			}
			hm->entries[index]->value = value;
			if (entryAtIndex != NULL) {
				*entryAtIndex = hm->entries[index];
			}
			return 1;
		}
		index = (index + 1) % hm->size;
	}
	hm->entries[index] = hme_create(AM_ALLOCATOR_ARG key, value);
	NULL_CHECK_RET_VAL(hm->entries[index], -1);
	hm->entries[index]->index = index;
	hm->count++;
	if (entryAtIndex != NULL) {
		*entryAtIndex = hm->entries[index];
	}
	return 0;
}

int hm_resize_insert(HashMapComparators* comparators,
					 HashMapEntry** entries,
					 size_t size,
					 HashMapEntry* entry,
					 size_t index) {
	while (entries[index] != NULL) {
		if (comparators->insertComparator(entry->key, entries[index]->key, entries[index]->value) == 0) {
			return -1;
		}
		index = (index + 1) % size;
	}
	entries[index] = entry;
	entries[index]->index = index;
	return 0;
}

int hm_resize(AM_ALLOCATOR_PARAM HashMap* hm) {
	size_t newSize = hm->size * 2;
	if (newSize < hm->size) {
		return -1;
	}
	HashMapEntry** newEntries = (HashMapEntry**) am_calloc(newSize, sizeof(HashMapEntry*));
	NULL_CHECK_RET_VAL(newEntries, -1);
	size_t hash;
	size_t index;
	for (int i = 0; i < hm->size; i++) {
		if (hm->entries[i] == NULL) {
			continue;
		}
		hash = HASH_FUNC(hm->entries[i]->key, hm->handlers.keySize);
		index = hash % newSize;
		if (hm_resize_insert(&hm->comparators, newEntries, newSize, hm->entries[i], index) != 0) {
			return -1;
		}
	}
	am_free(hm->entries);
	hm->entries = newEntries;
	hm->size = newSize;
	return 0;
}

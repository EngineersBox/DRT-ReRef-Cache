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

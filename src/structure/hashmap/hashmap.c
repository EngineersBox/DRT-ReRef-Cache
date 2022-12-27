#include "hashmap.h"

#include "../../utils/check.h"

HashMap* hm_create(AM_ALLOCATOR_PARAM size_t size, HashMapComparators comparators) {
	HashMap* map = (HashMap*) am_malloc(sizeof(*map));
	NULL_CHECK_RET_NULL(map);
	map->size = size;
	map->count = 0;
	map->comparators = comparators;
	map->entries = (HashMapEntry**) am_calloc(sizeof(HashMapEntry*), size);
	NULL_CHECK_RET_NULL(map->entries);
	return map;
}

void hm_destroy(AM_ALLOCATOR_PARAM HashMap* hm) {
	NULL_CHECK_RET_NONE(hm);
	NULL_CHECK_RET_NONE(hm->entries);
	for (int i = 0; i < hm->size; i++) {
		if (hm->items[i] == NULL) continue;
		hme_destroy(AM_ALLOCATOR_ARG hm->items[i]);
	}
	am_free(hm->items);
	am_free(hm);
}

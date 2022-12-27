#include "dequeue_hashmap.h"

#include "../../utils/check.h"

DequeueHashMap* dqhm_create(AM_ALLOCATOR_PARAM
							size_t size,
							HashMapComparators comparators,
							KeyHandlers handlers) {
	DequeueHashMap* dqhm = (DequeueHashMap*) am_malloc(sizeof(*dqhm));
	NULL_CHECK_RET_NULL(dqhm);
	dqhm->head = NULL;
	dqhm->tail = NULL;
	dqhm->hm = hm_create(AM_ALLOCATOR_ARG size, comparators, handlers);
	NULL_CHECK_RET_NULL(dqhm->hm);
	return dqhm;
}

void dqhm_destroy(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm) {
	NULL_CHECK_RET_NONE(dqhm);
	NULL_CHECK_RET_NONE(dqhm->hm);
	hm_destroy(dqhm->hm);
	am_free(dqhm);
}

void* dqhm_get(DequeueHashMap* dqhm, const char* key) {
	NULL_CHECK_RET_NULL(dqhm);
	NULL_CHECK_RET_NULL(dqhm->hm);
	NULL_CHECK_RET_NULL(key);
	return hm_get(dqhm->hm, key);
}

void dqhm_unlink(DequeueHashMap* dqhm, HashMapEntry* entry) {
	HashMapEntry* previousEntry = entry->previous;
	HashMapEntry* nextEntry = entry->next;
	if (previousEntry != NULL) {
		previousEntry->next = nextEntry;
	} else {
		dqhm->head = nextEntry;
	}
	if (nextEntry != NULL) {
		nextEntry->previous = previousEntry;
	} else {
		dqhm->tail = previousEntry;
	}
}

int dqhm_delete(AM_ALLOCATOR_PARAM DequeueHashMap* dqhm, const char* key, void** removed) {
	NULL_CHECK_RET_VAL(dqhm, -1);
	NULL_CHECK_RET_VAL(dqhm->hm, -1);
	NULL_CHECK_RET_VAL(key, -1);
	void* removedValue = hm_delete(AM_ALLOCATOR_ARG dqhm->hm, key);
	if (removed != NULL) {
		*removed = removedValue;
	}
	NULL_CHECK_RET_VAL(removedValue, 0);
	dqhm_unlink(dqhm, )
}

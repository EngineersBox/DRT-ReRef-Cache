#pragma once

#ifndef DRT_REREF_CACHE_CHECK_UTILS_H
#define DRT_REREF_CACHE_CHECK_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#define NULL_CHECK_RET_VAL_FREE(target, value, freeable) if ((target) == NULL) { am_free((freeable)); return (value); }
#define NULL_CHECK_RET_VAL(target, value) if ((target) == NULL) return (value)
#define NULL_CHECK_RET_NULL_FREE(target, freeable) NULL_CHECK_RET_VAL_FREE(target, NULL, freeable)
#define NULL_CHECK_RET_NULL(target) NULL_CHECK_RET_VAL(target, NULL)
#define NULL_CHECK_RET_NONE(target) if ((target) == NULL) return

#ifdef __cplusplus
}
#endif

#endif // DRT_REREF_CACHE_CHECK_UTILS_H

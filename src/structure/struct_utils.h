#pragma once

#ifndef DRT_REREF_CACHE_STRUCT_UTILS_H
#define DRT_REREF_CACHE_STRUCT_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

static void dump(void* ptr, long size) {
    printf("[START DUMP] Target: %p\n", ptr);
    const unsigned char* const struct_bytes = (unsigned char*) ptr;
    for (unsigned int i = 0; i < size; i++) {
        if (i % (sizeof(int) * 8) == 0) {
            printf("\n%08X ", i);
        } else if (i % 4 == 0) {
            printf(" ");
        }
        printf("%02X", struct_bytes[i]);
    }
    printf("\n[END DUMP] Target: %p\n", ptr);
}

#ifdef __cplusplus
};
#endif

#endif //DRT_REREF_CACHE_STRUCT_UTILS_H


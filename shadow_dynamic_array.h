//
// Created by paco on 18/10/26.
//

#ifndef SHADOW_DYNAMIC_ARRAY_H
#define SHADOW_DYNAMIC_ARRAY_H

#include <assert.h>
#include <stdlib.h>

#define ARRAY_INITIAL_CAPACITY 64

typedef struct {
    size_t count;
    size_t capacity;
} ArrayHeader;

#define array_init(array, capacity_)                                                \
    do {                                                                            \
    ArrayHeader* header = malloc(sizeof(ArrayHeader) + sizeof(*array) * capacity_); \
            header->count = 0;                                                      \
            header->capacity = capacity_;                                           \
            array = (void*)(header + 1);                                            \
    } while (0)

#define array_push(array, item)                                                                                 \
    do {                                                                                                        \
        if (array == nullptr) array_init(array, ARRAY_INITIAL_CAPACITY)                                         \
                                                                                                                \
        ArrayHeader* header = (ArrayHeader*)(array) - 1;                                                        \
        if (header->count >= header->capacity) {                                                                \
            header->capacity *= 1.5;                                                                            \
            ArrayHeader* new_header = realloc(header, sizeof(ArrayHeader) + sizeof(*array) * header->capacity); \
            assert(new_header != nullptr && "Error on realloc in array.");                                      \
            header = new_header;                                                                                \
            array = (void*)(header + 1);                                                                        \
        }                                                                                                       \
        (array)[header->count++] = (item);                                                                      \
    } while (0)

#define array_free(array) free((ArrayHeader*)(array) - 1)
#define array_length(array) ((ArrayHeader*)(array) - 1)->count
#define array_capacity(array) ((ArrayHeader*)(array) - 1)->capacity

#endif // SHADOW_DYNAMIC_ARRAY_H
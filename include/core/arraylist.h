#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include "sys/types.h"

#define arraylist_destroy(a) free((a)->array);

typedef struct {
    void *array;
    size_t item_size;
    size_t size;
    size_t mul_factor;
    size_t capacity;
} arraylist_t, *arraylist_p;

void arraylist_init(arraylist_p a, size_t item_size, size_t  starting_capacity, size_t mul_factor);
void arraylist_pushback(arraylist_p a, void *v);

#endif
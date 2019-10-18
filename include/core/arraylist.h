#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include "sys/types.h"

typedef void (*arraylist_iter_f)(void*);

#define arraylist_destroy(a) free((a)->array);

#define arraylist_iter(a, f) do                                                     \
{                                                                                   \
    for(int i = 0; i < (a)->size; i++) f((uint8_t*)(a)->array+i*(a)->item_size);    \
}                                                                                   \
while(0)

typedef struct {
    void *array;
    size_t item_size;
    size_t size;
    size_t mul_factor;
    size_t capacity;
} arraylist_t, *arraylist_p;

int arraylist_init(arraylist_p a, size_t item_size, size_t  starting_capacity, size_t mul_factor);
int arraylist_pushback(arraylist_p a, void *v);

#endif
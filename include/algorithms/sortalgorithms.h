#ifndef __SORTALGORITHMS_H__
#define __SORTALGORITHMS_H__
#include "core/typedefs.h"
#include "core/pessoa.h"

typedef void (*another_sort_f)(pessoa_t vec[], size_t vecSize, cmp_f cmp);

void selection_sort(void *ptr, size_t num, size_t size, cmp_f cmp);
void quick_sort(void *ptr, size_t num, size_t size, cmp_f cmp);
void insertion_sort(void *ptr, size_t num, size_t size, cmp_f cmp);
void merge_sort(pessoa_t vec[], size_t vecSize, cmp_f cmp);
void heap_sort(pessoa_t pessoas[], size_t array_size, cmp_f cmp);


#endif
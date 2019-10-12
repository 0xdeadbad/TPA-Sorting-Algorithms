#ifndef __SORTALGORITHMS_H__
#define __SORTALGORITHMS_H__
#include "core/typedefs.h"

void selection_sort(void *ptr, size_t num, size_t size, cmp_f cmp);
void quick_sort(void *ptr, size_t num, size_t size, cmp_f cmp);

#endif
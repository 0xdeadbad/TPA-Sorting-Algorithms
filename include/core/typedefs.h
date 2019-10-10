#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__
#include <stdint.h>
#include <sys/types.h>

/* 
 *  "Template" for comparison string
 *  Inspired by qsort compare function signature
 */
typedef int32_t (*cmp_f)(void*, void*);

/* 
 *  "Template" for sorting algorithm (to be used or not to be used, that's the question.) 
 *  Inspired by qsort function signature
 */
typedef void (*sorting_algorithm_f)(void *ptr, size_t num, size_t size, cmp_f cmp);

#endif
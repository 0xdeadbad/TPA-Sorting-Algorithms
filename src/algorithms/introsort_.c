#include <sys/types.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include "core/typedefs.h"
#include "core/util.h"
#include "core/pessoa.h"
#include "algorithms/sortalgorithms.h"

size_t partition(void *ptr, size_t num, size_t size, cmp_f cmp);

/*
def introsort(A):
	max_depth = math.log(len(A),2)
	return isort(A, max_depth)

def isort( A, max_depth):
	size = len(A)
	q = len(A)-1
	if len(A) <= 1:
		return A
	elif q > max_depth:
		heapsort(A)
	else:
		introsort(A[0:q], max_depth-1)
		introsort(A[q+1:], max_depth-1)
	return A
*/

void intro(void *ptr, size_t num, size_t size, cmp_f cmp, int32_t maxdepth) {
    uint8_t *start, *end;

    start = ptr;
    end = (uint8_t*)ptr+num*size;

    if(num <= 1)
        return;
    else if(num-1 > maxdepth) {
        heap_sort(ptr, num+1, cmp);
        return;
    }else if (start < end) {
        uint8_t *start, *end;

        start = ptr;
        end = (uint8_t*)ptr+num*size;
        
        if(end - start <= 0)
            return;

        size_t q;
        uint8_t *c, *d;

        q = partition(ptr, num, size, cmp);

        c = (uint8_t*)ptr+(q+1)*size;
        d = (uint8_t*)ptr+num*size;

        intro(ptr, q-1, size, cmp, maxdepth - 1);
        intro((uint8_t*)ptr+(q+1)*size, (d - c)/size, size, cmp, maxdepth - 1);
    }
    
}

void intro_sort(void *ptr, size_t num, size_t size, cmp_f cmp) {
    uint32_t maxdepth;

    maxdepth = log2(num) * 2;

    intro(ptr, num, size, cmp, maxdepth);
}
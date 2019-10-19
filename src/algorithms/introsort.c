#include <sys/types.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include "core/typedefs.h"
#include "core/util.h"
#include "core/pessoa.h"
#include "algorithms/sortalgorithms.h"

/*procedure sort(A : array):
    let maxdepth = ⌊log(length(A))⌋ × 2
    introsort(A, maxdepth)

procedure introsort(A, maxdepth):
    n ← length(A)
    if n ≤ 1:
        return  // base case
    else if maxdepth = 0:
        heapsort(A)
    else:
        p ← partition(A)  // assume this function does pivot selection, p is the final position of the pivot
        introsort(A[0:p-1], maxdepth - 1)
        introsort(A[p+1:n], maxdepth - 1)*/

size_t partition(void *ptr, size_t num, size_t size, cmp_f cmp);

void introsort(void *ptr, uint32_t num, size_t size, cmp_f cmp, uint32_t maxdepth) {

    if(num <= 1)
        return;
    else if(maxdepth == 0)
        heap_sort(ptr, num, cmp);
    else {
        size_t q;
        uint8_t *c, *d;

        printf("entrando\n");

        q = partition(ptr, num, size, cmp);

        printf("passou\n");

        c = (uint8_t*)ptr+(q+1)*size;
        d = (uint8_t*)ptr+num*size;

        introsort(ptr, q-1, size, cmp, maxdepth - 1);
        introsort((uint8_t*)ptr+(q+1)*size, (d - c)/size, size, cmp, maxdepth - 1);
    }
}

void intro_sort(void *ptr, size_t num, size_t size, cmp_f cmp) {
    uint32_t maxdepth;

    maxdepth = floor(log(num)) * 2;

    introsort(ptr, num, size, cmp, maxdepth);
}
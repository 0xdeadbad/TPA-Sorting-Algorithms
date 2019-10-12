#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>

#include "core/typedefs.h"
#include "core/util.h"

size_t partition(void *ptr, size_t num, size_t size, cmp_f cmp) {
    int i, j;

    i = 0;

    for(j = 1; j <= num; j++) 
        if(cmp((uint8_t*)ptr+j*size, ptr) < 0) 
            SWAP((uint8_t*)ptr+j*size, (uint8_t*)ptr+(++i)*size, size);

    SWAP(ptr, (uint8_t*)ptr+i*size, size);

    return i;
}

void quick_sort(void *ptr, size_t num, size_t size, cmp_f cmp) {
    uint8_t *a, *b;
    
    a = ptr;
    b = (uint8_t*)ptr+num*size;
    
    if(a < b) {
        int q;
        uint8_t *c, *d;

        q = partition(ptr, num, size, cmp);

        c = (uint8_t*)ptr+(q+1)*size;
        d = (uint8_t*)ptr+num*size;

        quick_sort(ptr, q-1, size, cmp);
        quick_sort((uint8_t*)ptr+(q+1)*size, (d - c)/size, size, cmp);
    }
}
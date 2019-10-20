#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "core/typedefs.h"
#include "core/util.h"

void insertion_sort(void *ptr, size_t num, size_t size, cmp_f cmp) {
    int i, j, chave;

    i = 0;

    for(j = 1; j < num; j++) {
        memcpy(&chave, (uint8_t*)ptr+j*size, size);
        i = j - 1;
        while(i >= 0 && cmp((uint8_t*)ptr+i*size, &chave)) {
            memcpy((uint8_t*)ptr+(i+1)*size, (uint8_t*)ptr+i*size, size);
            i--;
        }
            
        memcpy((uint8_t*)ptr+(i+1)*size, &chave, size);
    }
}
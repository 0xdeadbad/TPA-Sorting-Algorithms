#include "core/typedefs.h"
#include "core/util.h"

void selection_sort(void *ptr, size_t num, size_t size, cmp_f cmp) {
    uint32_t i, j;
    for(i = 0; i < num; i++) {
        uint32_t smallest = i;
        for(j = i + 1; j < num; j++) 
            if(cmp((uint8_t*)ptr+j*size, (uint8_t*)ptr+smallest*size) < 0)
                smallest = j;
        SWAP((uint8_t*)ptr+i*size, (uint8_t*)ptr+smallest*size, size);
    }
}
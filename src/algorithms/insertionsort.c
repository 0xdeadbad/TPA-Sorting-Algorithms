#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "core/typedefs.h"
#include "core/util.h"

/*
def insertionSort(l):
    ''' Ordena os elementos de uma lista em ordem crescente.
        Para isso, vai inserindo os elementos ordenadamente na própria lista..'''
    for k in range(1, len(l)):
        elem = l[k]
        pos = k

        while pos > 0 and l[pos - 1].uid > elem.uid:
            l[pos] = l[pos - 1]
            pos = pos - 1

        l[pos] = elem

    return l
*/

void insertion_sort(void *ptr, size_t num, size_t size, cmp_f cmp) {
    for(int k = 1; k <= num; k++) {
        void *elem;
        uint8_t *pos, *zero;

        elem = calloc(1, size);
        memcpy(elem, (uint8_t*)ptr+k*size, size);

        pos = (uint8_t*)ptr+k*size;
        zero = (uint8_t*)ptr;

        while(pos > zero && cmp((uint8_t*)pos-size, elem) > 0) {
            memcpy(pos, (uint8_t*)pos-size, size);
            pos -= size;
        }

        memcpy(pos, elem, size);
        free(elem);
    }
}
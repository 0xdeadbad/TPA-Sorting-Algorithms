#include "core/arraylist.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int arraylist_init(arraylist_p a, size_t item_size, size_t  starting_capacity, size_t mul_factor) {
	if((a->array = calloc(starting_capacity, item_size)) == NULL)
        return -1;
	a->item_size = item_size;
	a->size = 0;
	a->capacity = starting_capacity;
	a->mul_factor = mul_factor;

    return 0;
}

int arraylist_pushback(arraylist_p a, void *v) {
	if(a->size == a->capacity) {
		if((a->array = (arraylist_p) realloc(a->array, a->capacity*a->mul_factor*a->item_size)) == NULL)
        	return -1;
		a->capacity *= a->mul_factor;
		memset((uint8_t*)a->array+(a->item_size*a->size), 0, a->capacity-a->size);
	}

	memcpy((uint8_t*)a->array+(a->item_size*a->size++), v, a->item_size);

    return 0;
}
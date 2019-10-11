#include "core/arraylist.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void arraylist_init(arraylist_p a, size_t item_size, size_t  starting_capacity, size_t mul_factor) {
	a->array = calloc(starting_capacity, item_size);
	a->item_size = item_size;
	a->size = 0;
	a->capacity = starting_capacity;
	a->mul_factor = mul_factor;
}

void arraylist_pushback(arraylist_p a, void *v) {
	if(a->size == a->capacity) {
		a->array = (arraylist_p) realloc(a->array, a->capacity*a->mul_factor*a->item_size);
		a->capacity *= a->mul_factor;
		memset((uint8_t*)a->array+(a->item_size*a->size), 0, a->capacity-a->size);
	}

	memcpy((uint8_t*)a->array+(a->item_size*a->size++), v, a->item_size);
}
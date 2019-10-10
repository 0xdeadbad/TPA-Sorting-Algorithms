#ifndef __UTIL_H__
#define __UTIL_H__

/*
 *  Swap two values from an array
 *  Works for any type in compile time, as it is a MACRO.
 */
#define SWAP(array, T, a, b) do \
{                               \
    T aux = array[a];           \
    array[a] = array[b];        \
    array[b] = aux;             \
} while (0);

#endif
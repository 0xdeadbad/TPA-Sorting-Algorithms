#include "core/typedefs.h"
#include "core/util.h"
#include "core/pessoa.h"
#include "algorithms/sortalgorithms.h"

#include <stdlib.h>
#include <stdio.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))


const int RUN = 32;

void merge(pessoa_t vec[], size_t vecSize, cmp_f cmp);

// iterative Timsort function to sort the 
// array[0...n-1] (similar to merge sort) 
void tim_sort(pessoa_t arr[], size_t n, cmp_f cmp) 
{ 

    // Sort individual subarrays of size RUN 
    for (int i = 0; i < n; i += RUN) {
        pessoa_p a, b;

        printf("b");
        
        a = arr;
        b = arr+min((i+31), (n-1));

        printf("a");

        insertion_sort(arr+i, b-a, sizeof(pessoa_t), cmp); 
    }
    
    // start merging from size RUN (or 32). It will merge 
    // to form size 64, then 128, 256 and so on .... 
    for (int size = RUN; size < n; size = 2*size) 
    { 
        // pick starting point of left sub array. We 
        // are going to merge arr[left..left+size-1] 
        // and arr[left+size, left+2*size-1] 
        // After every merge, we increase left by 2*size 
        for (int left = 0; left < n; left += 2*size) 
        { 
            // find ending point of left sub array 
            // mid+1 is starting point of right sub array
            int right = min((left + 2*size - 1), (n-1)); 
  
            // merge sub array arr[left.....mid] & 
            // arr[mid+1....right] 
            merge(arr, right-left, cmp); 
        } 
    } 
} 
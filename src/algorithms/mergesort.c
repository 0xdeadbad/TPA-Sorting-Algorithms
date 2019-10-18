#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/util.h"
#include "core/typedefs.h"
#include "core/pessoa.h"

void merge(pessoa_t vec[], size_t vecSize, cmp_f cmp) {
  int mid;
  int i, j, k;
  pessoa_p tmp;
 
  tmp = (pessoa_p) malloc(vecSize * sizeof(pessoa_t));
  if (tmp == NULL) {
    exit(1);
  }
 
  mid = vecSize / 2;
 
  i = 0;
  j = mid;
  k = 0;
  while (i < mid && j < vecSize) {
    // vec[i] < vec[j]
    if (cmp(vec+i, vec+j) < 0) {
      tmp[k] = vec[i];
      ++i;
    }
    else {
      tmp[k] = vec[j];
      ++j;
    }
    ++k;
  }
 
  if (i == mid) {
    while (j < vecSize) {
      tmp[k] = vec[j];
      ++j;
      ++k;
    }
  }
  else {
    while (i < mid) {
      tmp[k] = vec[i];
      ++i;
      ++k;
    }
  }
 
  for (i = 0; i < vecSize; ++i) {
    vec[i] = tmp[i];
  }
 
  free(tmp);
}
 
void merge_sort(pessoa_t vec[], size_t vecSize, cmp_f cmp) {
  int mid;
 
  if (vecSize > 1) {
    mid = vecSize / 2;
    merge_sort(vec, mid, cmp);
    merge_sort(vec + mid, vecSize - mid, cmp);
    merge(vec, vecSize, cmp);
  }
}
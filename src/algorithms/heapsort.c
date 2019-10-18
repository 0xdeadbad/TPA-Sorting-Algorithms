#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "core/typedefs.h"
#include "core/util.h"
#include "core/pessoa.h"

#include "stdio.h"
#include "stdlib.h"

void siftDown(pessoa_t pessoas[], int root, int bottom, cmp_f cmp)
{
  int done, maxChild;
  pessoa_t temp;
 
  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (cmp(pessoas+root*2, pessoas+root*2+1) > 0)
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
 
    if (cmp(pessoas+root, pessoas+maxChild) < 0)
    {
      temp = pessoas[root];
      pessoas[root] = pessoas[maxChild];
      pessoas[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

void heap_sort(pessoa_t pessoas[], size_t array_size, cmp_f cmp)
{
  int i;

  pessoa_t temp;
 
  for (i = (array_size / 2); i >= 0; i--)
    siftDown(pessoas, i, array_size - 1, cmp);
 
  for (i = array_size-1; i >= 1; i--)
  {
    temp = pessoas[0];
    pessoas[0] = pessoas[i];
    pessoas[i] = temp;
    siftDown(pessoas, 0, i-1, cmp);
  }
}
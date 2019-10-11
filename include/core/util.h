#ifndef __UTIL_H__
#define __UTIL_H__
#include <sys/types.h>
#include <stdint.h>

/*
 *  Swap two values from an array
 *  Works for any type in compile time, as it is a MACRO.
 */
#define SWAP(a, b, size)                                                      \
  do                                                                          \
    {                                                                         \
      size_t __size = (size);                                                 \
      uint8_t *__a = (a), *__b = (b);                                            \
      do                                                                      \
        {                                                                     \
          uint8_t __tmp = *__a;                                                  \
          *__a++ = *__b;                                                      \
          *__b++ = __tmp;                                                     \
        } while (--__size > 0);                                               \
    } while (0)

#endif
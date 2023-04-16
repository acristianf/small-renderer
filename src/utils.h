#ifndef _UTILS_H
#define _UTILS_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "model.h"

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))

#define MAX_STRING_BUFFER_SIZE 256

#define ARRAY_UPDATE_FACTOR 2
#define ARRAY_INIT_CAP 8

inline void swap(Vertex *a, Vertex *b) {
  if (a != b) { // Check if addresses are different
    Vertex temp = *a;
    *a = *b;
    *b = temp;
  }
}

inline void swap(int *a, int *b) {
  if (a != b) { // Check if addresses are different
    int temp = *a;
    *a = *b;
    *b = temp;
  }
}

inline int abs_fast(int32_t x) {
  uint32_t mask = x >> 31;
  x ^= mask;
  x += mask & 1;
  return x;
}

#endif

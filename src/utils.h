#ifndef _UTILS_H
#define _UTILS_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "geometry.h"
#include "model.h"

#define PI 3.14159265359

#define DEGREE_TO_RADIAN(deg) (deg * (PI / 180.f))

#define ASSERT(condition)                                                      \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #condition,  \
              __FILE__, __LINE__);                                             \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

#define MAX_STRING_BUFFER_SIZE 256

#define ARRAY_UPDATE_FACTOR 2
#define ARRAY_INIT_CAP 8

inline void swap(Vec3f *a, Vec3f *b) {
  if (a != b) { // Check if addresses are different
    Vec3f temp = *a;
    *a = *b;
    *b = temp;
  }
}

inline void swap(Vertex *a, Vertex *b) {
  if (a != b) { // Check if addresses are different
    Vertex temp = *a;
    *a = *b;
    *b = temp;
  }
}

inline void swap(double *a, double *b) {
  if (a != b) { // Check if addresses are different
    int temp = *a;
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

// Returns 0 if decimal_places is less than 1
inline double round(double x, int decimal_places) {
  if (decimal_places >= 1) {
    double factor = pow(10.0f, decimal_places);
    return round(x * factor) / factor;
  }
  return 0;
}

#endif

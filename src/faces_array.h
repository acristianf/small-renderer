#ifndef _FACESARRAY_H
#define _FACESARRAY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "utils.h"

typedef struct FacesArray {
  Face *data;
  size_t size; // Current size
  size_t cap;  // Max cap
} FacesArray;

FacesArray faces_array_init();
void faces_array_append(FacesArray *arr, Face data);
Face faces_array_get(FacesArray *arr, size_t index);
void faces_array_set(FacesArray *arr, size_t index, Face data);
void faces_array_free(FacesArray *arr);
void print_faces_array(FacesArray *arr);

#endif

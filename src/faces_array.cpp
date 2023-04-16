
#include "faces_array.h"

FacesArray faces_array_init() {
  FacesArray arr = {};
  return arr;
}

void faces_array_append(FacesArray *arr, Face data) {
  if (arr->cap == 0) {
    arr->cap = ARRAY_INIT_CAP;
    arr->data = (Face *)malloc(sizeof(Face) * arr->cap);
    arr->size = 0;
  } else if (arr->size == arr->cap - 1) {
    size_t new_cap = arr->cap * ARRAY_UPDATE_FACTOR;
    arr->data = (Face *)realloc(arr->data, sizeof(Face) * new_cap);
    arr->cap = new_cap;
  }
  arr->data[arr->size] = data;
  arr->size++;
}

// Returns the desired Face or an empty one if not found
Face faces_array_get(FacesArray *arr, size_t index) {
  if (arr->cap != 0 && index <= arr->size) {
    return arr->data[index];
  }
  return Face();
}

void faces_array_set(FacesArray *arr, size_t index, Face data) {
  if (arr->cap != 0 && index <= arr->size) {
    Face *tmp = &arr->data[index];
    arr->data[index] = data;
    free(tmp);
  }
}

void faces_array_free(FacesArray *arr) {
  if (arr->cap != 0) {
    free(arr->data);
  }
}

void print_faces_array(FacesArray *arr) {
  for (size_t i = 0; i < arr->size; i++) {
    print_face(&arr->data[i]);
  }
}

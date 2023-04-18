#include "vertex_array.h"

void vertex_array_init(dynVertexArray *arr) {
  arr->data = NULL;
  arr->size = 0;
  arr->cap = 0;
}

void vertex_array_append(dynVertexArray *arr, Vertex data) {
  if (arr->cap == 0) {
    arr->cap = ARRAY_INIT_CAP;
    arr->data = (Vertex *)malloc(sizeof(Vertex) * arr->cap);
    arr->size = 0;
  } else if (arr->size == arr->cap - 1) {
    size_t new_cap = arr->cap * ARRAY_UPDATE_FACTOR;
    arr->data = (Vertex *)realloc(arr->data, sizeof(Vertex) * new_cap);
    arr->cap = new_cap;
  }
  arr->data[arr->size] = data;
  arr->size++;
}

// Returns the desired Vertex or an empty one if not found
Vertex vertex_array_get(dynVertexArray *arr, size_t index) {
  if (arr->cap != 0 && index <= arr->size) {
    return arr->data[index];
  }
  return Vertex();
}

void vertex_array_set(dynVertexArray *arr, size_t index, Vertex data) {
  if (arr->cap != 0 && index <= arr->size) {
    Vertex *tmp = &arr->data[index];
    arr->data[index] = data;
    free(tmp);
  }
}

void vertex_array_free(dynVertexArray *arr) {
  if (arr->cap != 0) {
    free(arr->data);
  }
}

static void bubble_sort(dynVertexArray *arr) {
  for (size_t i = 0; i < arr->size - 1; i++) {
    for (size_t j = 0; j < arr->size - i - 1; j++) {
      if (arr->data[j].y > arr->data[j + 1].y) {
        swap(&arr->data[j], &arr->data[j + 1]);
      }
    }
  }
}

void sort_vertex_array(dynVertexArray *arr) { bubble_sort(arr); }

void print_vertex_array(dynVertexArray *arr) {
  for (size_t i = 0; i < arr->size; i++) {
    printf("%zu: ", i);
    print_vertex(&arr->data[i]);
  }
}

#ifndef _VERTEXARRAY_H
#define _VERTEXARRAY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "utils.h"

typedef struct dynVertexArray {
  Vertex *data;
  size_t size; // Current size
  size_t cap;  // Max cap
} dynVertexArray;

// VertexArray vertex_array_init();
void vertex_array_init(dynVertexArray *arr);
void vertex_array_append(dynVertexArray *arr, Vertex data);
Vertex vertex_array_get(dynVertexArray *arr, size_t index);
void vertex_array_set(dynVertexArray *arr, size_t index, Vertex data);
void vertex_array_free(dynVertexArray *arr);
void print_vertex_array(dynVertexArray *arr);
void sort_vertex_array(dynVertexArray *arr);

#endif

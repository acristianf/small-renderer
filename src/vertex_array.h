#ifndef _VERTEXARRAY_H
#define _VERTEXARRAY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "utils.h"

typedef struct VertexArray {
  Vertex *data;
  size_t size; // Current size
  size_t cap;  // Max cap
} VertexArray;

// VertexArray vertex_array_init();
void vertex_array_init(VertexArray *arr);
void vertex_array_append(VertexArray *arr, Vertex data);
Vertex vertex_array_get(VertexArray *arr, size_t index);
void vertex_array_set(VertexArray *arr, size_t index, Vertex data);
void vertex_array_free(VertexArray *arr);
void print_vertex_array(VertexArray *arr);
void sort_vertex_array(VertexArray *arr);

#endif

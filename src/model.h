#ifndef _MODEL_H
#define _MODEL_H

#include <stdint.h>
#include <stdio.h>

typedef struct Vertex {
  double x;
  double y;
  double z;
} Vertex;

typedef struct Face {
  uint32_t v1;
  uint32_t v2;
  uint32_t v3;
  uint32_t vt1;
  uint32_t vt2;
  uint32_t vt3;
} Face;

inline void print_vertex(Vertex *vertex) {
  printf("Vertex(%f, %f, %f)\n", vertex->x, vertex->y, vertex->z);
}

inline void print_face(Face *face) {
  printf("Face(v: %d, %d, %d; vt: %d, %d, %d)\n", face->v1, face->v2, face->v3,
         face->vt1, face->vt2, face->vt3);
}

#endif

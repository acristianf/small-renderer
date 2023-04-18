#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <math.h>

#include "model.h"

typedef struct Vec2i {
  int x;
  int y;
} Vec2i;

typedef struct Vec2f {
  double x;
  double y;
} Vec2f;

typedef struct Vec3f {
  double x;
  double y;
  double z;
} Vec3f;

typedef struct Vec3Vertex {
  Vertex v0;
  Vertex v1;
  Vertex v2;
} Vec3Vertex;

Vec3f barycentric_coordinates(Vertex *pts, Vec3f P);
Vec3f cross_product(Vec3f v1, Vec3f v2);
double scalar_product(Vec3f v1, Vec3f v2);
void normalize(Vec3f *v);
inline void print_vector(Vec3f *v) {
  printf("Vector(%f, %f, %f)\n", v->x, v->y, v->z);
}

#endif

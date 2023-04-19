#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <math.h>

#include "model.h"

typedef struct Vec3f {
  double x;
  double y;
  double z;
} Vec3f;

typedef struct Matrix44f {
  double data[4][4];
} Matrix44f;

Vec3f barycentric_coordinates(Vertex *pts, Vec3f P);

// Vectors

Vec3f cross_product(Vec3f v1, Vec3f v2);
Vec3f add(Vec3f *v1, Vec3f *v2);
Vec3f sub(Vec3f *v1, Vec3f *v2);
Vec3f mult(Vec3f *v1, Vec3f *v2);
double length(Vec3f *v);
void normalize(Vec3f *v);
double dot_product(Vec3f v1, Vec3f v2);
Vec3f spherical_to_cartesian(double theta, double phi);
double spherical_theta(Vec3f *v);
double spherical_phi(Vec3f *v);
inline void print_vector(Vec3f *v) {
  printf("Vector(%f, %f, %f)\n", v->x, v->y, v->z);
}

// Matrix

Matrix44f mult(Matrix44f *m1, Matrix44f *m2);
void mult(Matrix44f *m, Vec3f *v, Vec3f *dst);
// Returns the transposed matrix of the given one.
Matrix44f transpose(Matrix44f *m);
void to_identity(Matrix44f *m);
void invert_it(Matrix44f *m);
inline void print_matrix(Matrix44f *m) {
  for (int i = 0; i < 4; i++) {
    printf("Row%d(%f, %f, %f, %f)\n", i, m->data[i][0], m->data[i][1],
           m->data[i][2], m->data[i][3]);
  }
}

#endif

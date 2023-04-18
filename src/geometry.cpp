#include "geometry.h"

Vec3f barycentric_coordinates(Vertex *pts, Vec3f P) {
  Vec3f bary_coords = {-1, -1, -1};

  Vertex A = pts[0];
  Vertex B = pts[1];
  Vertex C = pts[2];

  float alpha = 0.f;
  float beta = 0.f;
  float gamma = 0.f;

  alpha = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) /
          ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));
  beta = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) /
         ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));
  gamma = 1 - alpha - beta;

  bary_coords.x = alpha;
  bary_coords.y = beta;
  bary_coords.z = gamma;

  return bary_coords;
};

Vec3f cross_product(Vec3f v1, Vec3f v2) {
  return Vec3f{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
               v1.x * v2.y - v1.y * v2.x};
};

double scalar_product(Vec3f v1, Vec3f v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void normalize(Vec3f *v) {
  double length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  v->x = v->x / length;
  v->y = v->y / length;
  v->z = v->z / length;
};

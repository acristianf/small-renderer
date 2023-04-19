#include "geometry.h"
#include "utils.h"

Vec3f add(Vec3f *v1, Vec3f *v2) {
  return Vec3f{v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
};

Vec3f sub(Vec3f *v1, Vec3f *v2) {
  return Vec3f{v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
};

Vec3f mult(Vec3f *v1, Vec3f *v2) {
  return Vec3f{v1->x * v2->x, v1->y * v2->y, v1->z * v2->z};
};

Vec3f cross_product(Vec3f v1, Vec3f v2) {
  return Vec3f{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
               v1.x * v2.y - v1.y * v2.x};
};

double dot_product(Vec3f v1, Vec3f v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double length(Vec3f *v) {
  return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void normalize(Vec3f *v) {
  double l = 1 / length(v);
  if (l > 0) {
    v->x = v->x * l;
    v->y = v->y * l;
    v->z = v->z * l;
  }
};

Matrix44f mult(Matrix44f *m1, Matrix44f *m2) {
  Matrix44f mult;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      mult.data[i][j] =
          m1->data[i][0] * m2->data[0][j] + m1->data[i][1] * m2->data[1][j] +
          m1->data[i][2] * m2->data[2][j] + m1->data[i][3] * m2->data[3][j];
    }
  }
  return mult;
}

Matrix44f transpose(Matrix44f *m) {
  Matrix44f transposed = {};
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      transposed.data[i][j] = m->data[j][i];
      transposed.data[i][j] = m->data[j][i];
      transposed.data[i][j] = m->data[j][i];
      transposed.data[i][j] = m->data[j][i];
    }
  }
  return transposed;
};

void to_identity(Matrix44f *m) {
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      if (i == j) {
        m->data[i][i] = 1;
      } else {
        m->data[i][j] = 0;
      }
    }
  }
};

void invert_it(Matrix44f *m) {
  Matrix44f original = *m;
  to_identity(m);
  for (uint32_t column = 0; column < 4; ++column) {
    // Swap row in case our pivot point is not working
    if (original.data[column][column] == 0) {
      uint32_t big = column;
      for (uint32_t row = 0; row < 4; ++row)
        if (fabs(original.data[row][column]) > fabs(original.data[big][column]))
          big = row;
      // Print this as a singular matrix, return identity?
      if (big == column)
        fprintf(stderr, "Singular matrix\n");
      // Swap rows
      else
        for (uint32_t j = 0; j < 4; ++j) {
          swap(&m->data[column][j], &m->data[big][j]);
          swap(&original.data[column][j], &original.data[big][j]);
        }
    }
  }
  for (uint32_t column = 0; column < 3; ++column) {
    // Make each row in column = 0. Proceed top to bottom
    for (uint32_t row = column + 1; row < 4; ++row) {
      // that's our constant k
      double constant =
          original.data[row][column] / original.data[column][column];
      // process each coefficient on the current row
      for (uint32_t j = 0; j < 4; ++j) {
        original.data[row][j] -= constant * original.data[column][j];
        m->data[row][j] -= constant * m->data[column][j];
      }
      // Set the element to 0 for safety
      original.data[row][column] = 0;
    }
  }
  for (uint32_t row = 0; row < 4; ++row) {
    float divisor = original.data[row][row];
    for (uint32_t column = 0; column < 4; ++column) {
      original.data[row][column] = original.data[row][column] / divisor;
      m->data[row][column] = m->data[row][column] / divisor;
    }
  }
  // for each row
  for (uint32_t row = 0; row < 4; ++row) {
    // for each coefficient above the diagonal for this row
    for (uint32_t column = row + 1; column < 4; ++column) {
      double constant = original.data[row][column];
      for (uint32_t k = 0; k < 4; ++k) {
        original.data[row][k] -= original.data[column][k] * constant;
        m->data[row][k] -= m->data[column][k] * constant;
      }
      // in case of a round-off error
      original.data[row][column] = 0.f;
    }
  }
};

void mult(Matrix44f *m, Vec3f *v, Vec3f *dst) {
  dst->x = m->data[0][0] * v->x + m->data[1][0] * v->y + m->data[2][0] * v->z +
           m->data[3][0];
  dst->y = m->data[0][1] * v->x + m->data[1][1] * v->y + m->data[2][1] * v->z +
           m->data[3][1];
  dst->z = m->data[0][2] * v->x + m->data[1][2] * v->y + m->data[2][2] * v->z +
           m->data[3][2];
};

Vec3f spherical_to_cartesian(double theta, double phi) {
  return Vec3f{cos(phi) * sin(theta), sin(theta) * sin(phi), cos(theta)};
};

double spherical_theta(Vec3f *v) {
  double z = v->z * 1 / length(v);
  return acos(z);
};

double spherical_phi(Vec3f *v) {
  double phi = atan2(v->y, v->x);
  return (phi < 0) ? phi + 2 * PI : phi;
};

Vec3f barycentric_coordinates(Vertex *pts, Vec3f P) {
  Vec3f bary_coords = {-1, -1, -1};

  Vertex A = pts[0];
  Vertex B = pts[1];
  Vertex C = pts[2];

  double alpha = 0.f;
  double beta = 0.f;
  double gamma = 0.f;

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

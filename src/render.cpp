#include "render.h"

void init_zbuffer(Zbuffer *zbuf, size_t width, size_t height) {
  zbuf->data = (double *)malloc(sizeof(double) * width * height);
  zbuf->width = width;
  zbuf->height = height;
  for (size_t i = 0; i < width * height; i++) {
    zbuf->data[i] = INT_MIN;
  }
}

void free_zbuffer(Zbuffer *zbuf) {
  free(zbuf->data);
  zbuf->width = 0;
  zbuf->height = 0;
}

double find_at(Zbuffer *zbuf, int x, int y) {
  ASSERT((size_t)x > 0);
  ASSERT((size_t)x < zbuf->width);
  ASSERT((size_t)y > 0);
  ASSERT((size_t)y < zbuf->height);

  return zbuf->data[x + y * zbuf->width];
}

void replace_at(Zbuffer *zbuf, int x, int y, double val) {
  ASSERT((size_t)x > 0);
  ASSERT((size_t)x < zbuf->width);
  ASSERT((size_t)y > 0);
  ASSERT((size_t)y < zbuf->height);

  zbuf->data[x + y * zbuf->width] = val;
}

// Dray a 2d scene on a 1d screen
void rasterize(Vec3f p0, Vec3f p1, TGAImage *render, TGAColor color,
               int buffer[]) {
  // Make it left to right
  if (p0.x > p1.x) {
    swap(&p0, &p1);
  }

  int dx = p1.x - p0.x;
  for (int x = p0.x; x <= p1.x; x++) {
    double t = (x - p0.x) / (double)dx;
    int y = rint(p0.y * (1.f - t) + p1.y * t);
    if (buffer[x] < y) {
      buffer[x] = y;
      for (int i = 0; i < render->get_height(); i++) {
        render->set(x, i, color);
      }
    }
  }
}

void render_line(int x0, int x1, int y0, int y1, TGAColor color,
                 TGAImage *img) {
  bool steep = false;
  // If the line is steep, transpose the image
  if (abs_fast(x0 - x1) < abs_fast(y0 - y1)) {
    swap(&x0, &y0);
    swap(&x1, &y1);
    steep = true;
  }

  // Make it left to right
  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  // Check boundaries
  if (x0 < 0 || x1 > img->get_width() || y0 < 0 || y1 > img->get_width()) {
    // TODO: Log this
    // fprintf(stderr, "Render error: Line out of boundaries. Skipping..\n");
    return;
  }

  int dx = x1 - x0;
  for (int x = x0; x <= x1; x++) {
    double t = (x - x0) / (double)dx;
    int y = rint(y0 * (1.f - t) + y1 * t); // rint = fast round
    if (steep) {
      img->set(y, x, color); // If transposed, de-transpose
    } else {
      img->set(x, y, color);
    }
  }
}

void render_line(Vec3f p0, Vec3f p1, TGAColor color, TGAImage *img) {
  bool steep = false;
  // If the line is steep, transpose the image
  if (abs_fast(p0.x - p1.x) < abs_fast(p0.y - p1.y)) {
    swap(&p0.x, &p0.y);
    swap(&p1.x, &p1.y);
    steep = true;
  }

  // Make it left to right
  if (p0.x > p1.x) {
    swap(&p0, &p1);
  }

  // Check boundaries
  if (p0.x < 0 || p1.x > img->get_width() || p0.y < 0 ||
      p1.y > img->get_width()) {
    // TODO: Log this
    // fprintf(stderr, "Render error: Line out of boundaries. Skipping..\n");
    return;
  }

  int dx = p1.x - p0.x;
  for (int x = p0.x; x <= p1.x; x++) {
    double t = (x - p0.x) / (double)dx;
    int y = rint(p0.y * (1.f - t) + p1.y * t); // rint = fast round
    if (steep) {
      img->set(y, x, color); // If transposed, de-transpose
    } else {
      img->set(x, y, color);
    }
  }
};

void render_triangle(Vertex pts[], TGAImage *image, TGAColor color) {

  Vec3f bboxmin = {(double)image->get_width() - 1,
                   (double)image->get_height() - 1};
  Vec3f bboxmax = {0.0, 0.0};
  Vec3f clamp = {(double)image->get_width() - 1,
                 (double)image->get_height() - 1};
  for (int i = 0; i < 3; i++) {
    bboxmin.x = MAX(0, MIN(bboxmin.x, pts[i].x));
    bboxmin.y = MAX(0, MIN(bboxmin.y, pts[i].y));

    bboxmax.x = MIN(clamp.x, MAX(bboxmax.x, pts[i].x));
    bboxmax.y = MIN(clamp.y, MAX(bboxmax.y, pts[i].y));
  }

  Vec3f P = {0.0, 0.0, 0.0};
  for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
    for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
      Vec3f barycentric = barycentric_coordinates(pts, P);
      if (barycentric.x >= 0 && barycentric.y >= 0 && barycentric.z >= 0)
        image->set(P.x, P.y, color);
    }
  }
}

void render_triangle(Vertex pts[], Zbuffer zbuffer, TGAImage *image,
                     TGAColor color) {
  Vec3f bboxmin = {(double)image->get_width() - 1,
                   (double)image->get_height() - 1};
  Vec3f bboxmax = {0.0, 0.0};
  Vec3f clamp = {(double)image->get_width() - 1,
                 (double)image->get_height() - 1};
  for (int i = 0; i < 3; i++) {
    bboxmin.x = MAX(0, MIN(bboxmin.x, pts[i].x));
    bboxmin.y = MAX(0, MIN(bboxmin.y, pts[i].y));

    bboxmax.x = MIN(clamp.x, MAX(bboxmax.x, pts[i].x));
    bboxmax.y = MIN(clamp.y, MAX(bboxmax.y, pts[i].y));
  }

  Vec3f P = {0.0, 0.0, 0.0};
  for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
    for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
      Vec3f barycentric = barycentric_coordinates(pts, P);
      if (barycentric.x >= 0 && barycentric.y >= 0 && barycentric.z >= 0) {
        // Calculate the z coords (the depth)
        double bc_screen[3] = {barycentric.x, barycentric.y, barycentric.z};
        for (int i = 0; i < 3; i++)
          P.z += pts[i].z * bc_screen[i];
        // Draw only if is superior to other depths
        if (find_at(&zbuffer, (int)P.x, (int)P.y) < P.z) {
          replace_at(&zbuffer, (int)P.x, (int)P.y, P.z);
          image->set(P.x, P.y, color);
        }
      }
    }
  }
}

void render_triangle(Vertex pts[], Vertex txt_verts[], Zbuffer *zbuffer,
                     TGAImage *image, TGAImage *texture, double intensity) {
  Vec3f bboxmin = {(double)image->get_width() - 1,
                   (double)image->get_height() - 1};
  Vec3f bboxmax = {0.0, 0.0};
  Vec3f clamp = {(double)image->get_width() - 1,
                 (double)image->get_height() - 1};
  for (int i = 0; i < 3; i++) {
    bboxmin.x = MAX(0, MIN(bboxmin.x, pts[i].x));
    bboxmin.y = MAX(0, MIN(bboxmin.y, pts[i].y));

    bboxmax.x = MIN(clamp.x, MAX(bboxmax.x, pts[i].x));
    bboxmax.y = MIN(clamp.y, MAX(bboxmax.y, pts[i].y));
  }

  // uv coordinates for texture mapping
  Vec3f Puv = {};
  Vec3f A;
  Vec3f B;
  Vec3f C;

  TGAColor color = {255, 255, 255, 255};
  Vec3f P = {0.0, 0.0, 0.0};
  for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
    for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
      Vec3f barycentric = barycentric_coordinates(pts, P);
      if (barycentric.x >= -0.03 && barycentric.y >= -0.03 &&
          barycentric.z >= -0.03) {
        // Calculate the z coords (the depth)
        double bc_screen[3] = {barycentric.x, barycentric.y, barycentric.z};
        for (int i = 0; i < 3; i++)
          P.z += pts[i].z * bc_screen[i];
        // Draw only if is superior to other depths
        if (find_at(zbuffer, (int)P.x, (int)P.y) < P.z) {

          replace_at(zbuffer, (int)P.x, (int)P.y, P.z);

          // Interpolate texture coordinates
          A = {barycentric.x * txt_verts[0].x, barycentric.x * txt_verts[0].y};
          B = {barycentric.y * txt_verts[1].x, barycentric.y * txt_verts[1].y};
          C = {barycentric.z * txt_verts[2].x, barycentric.z * txt_verts[2].y};
          Puv = {A.x + B.x + C.x, A.y + B.y + C.y};
          Puv = {Puv.x * texture->get_width(),
                 texture->get_height() - Puv.y * texture->get_height()};

          color = texture->get(Puv.x, Puv.y);

          color.r = color.r * intensity;
          color.g = color.g * intensity;
          color.b = color.b * intensity;

          image->set(P.x, P.y, color);
        }
      }
    }
  }
};

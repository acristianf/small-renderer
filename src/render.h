#ifndef _RENDER_H
#define _RENDER_H

#include "geometry.h"
#include "model.h"
#include "tgaimage.h"
#include "utils.h"

typedef struct Zbuffer {
  size_t width;
  size_t height;
  double *data;
} Zbuffer;

void render_line(int x0, int x1, int y0, int y1, TGAColor color, TGAImage *img);
void render_triangle(Vertex pts[], TGAImage *image, TGAColor color);
void render_triangle(Vertex pts[], Zbuffer zbuffer, TGAImage *image,
                     TGAColor color);
void render_triangle(Vertex pts[], Vertex txt_verts[], Zbuffer *zbuffer,
                          TGAImage *image, TGAImage *texture, double intensity);
void rasterize(Vec2i p0, Vec2i p1, TGAImage *render, TGAColor, int buffer[]);

// Zbuffer methods
void init_zbuffer(Zbuffer *zbuf, size_t width, size_t height);
void free_zbuffer(Zbuffer *zbuf);
double find_at(Zbuffer *zbuf, int x, int y);
void replace_at(Zbuffer *zbuf, int x, int y, double val);

#endif

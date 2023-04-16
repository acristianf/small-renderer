#ifndef _RENDER_H
#define _RENDER_H

#include "model.h"
#include "tgaimage.h"

void render_line(int x0, int x1, int y0, int y1, TGAColor color, TGAImage *img);
void render_2dtriangle(Vertex v0, Vertex v1, Vertex v2, TGAImage *image,
                       TGAColor color);

#endif

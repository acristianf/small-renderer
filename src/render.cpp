#include "render.h"
#include "utils.h"
#include "vertex_array.h"

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
  // int dy = y1 - y0;
  for (int x = x0; x <= x1; x++) {
    float t = (x - x0) / (float)dx;
    int y = rint(y0 * (1.f - t) + y1 * t); // rint = fast round
    if (steep) {
      img->set(y, x, color); // If transposed, de-transpose
    } else {
      img->set(x, y, color);
    }
  }
}

// static void sweep_2dtriangle(Vertex v0, Vertex v1, Vertex v2, TGAImage
// *image,
//                              TGAColor color){
//
// };

void render_2dtriangle(Vertex v0, Vertex v1, Vertex v2, TGAImage *image,
                       TGAColor color) {
  if (v0.y > v1.y)
    swap(&v0, &v1);
  if (v0.y > v2.y)
    swap(&v0, &v2);
  if (v1.y > v2.y)
    swap(&v1, &v2);
  render_line(v0.x, v2.x, v0.y, v2.y, TGAColor(255, 0, 0, 255), image);
  render_line(v0.x, v1.x, v0.y, v1.y, TGAColor(0, 255, 0, 255), image);
  render_line(v1.x, v2.x, v1.y, v2.y, TGAColor(0, 255, 0, 255), image);
  // TODO: CONTINUE THIS

  float base_length = v0.x - v2.x;
  float mid_x = (v0.x + v2.x / 2);
  for (float t = .0; t < 1; t += 0.005) {
    float x0 = v0.x + (base_length * t);
    float x1 = v2.x + (base_length * t);
    float y0 = v0.y;
    float y1 = v2.y;
    render_line(x0, x1, y0, y1, color, image);
    render_line(x0, x1, y0, y1, color, image);
  }

  // render_line(v0.x, v1.x, v0.y, v1.y, color, image);
  // render_line(v1.x, v2.x, v1.y, v2.y, color, image);
  // render_line(v2.x, v0.x, v2.y, v0.y, color, image);
}

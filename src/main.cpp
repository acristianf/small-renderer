#include <string.h>

#include <stdio.h>

#include "faces_array.h"
#include "render.h"
#include "tgaimage.h"
#include "tiny_obj_parser.h"
#include "utils.h"
#include "vertex_array.h"

#define BUILD_DIR "./build/"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const int WIDTH = 1000;
const int HEIGHT = 1000;
const int PADDING = 15;

int main(int argc, char **argv) {
  printf("Render start...\n");

  TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

  VertexArray vertex_array;
  vertex_array_init(&vertex_array);
  FacesArray faces_array = faces_array_init();

  parse_obj("./data/head.obj", &vertex_array, &faces_array);

  Vertex v1 = {10 * 5, 70 * 5, 0};
  Vertex v2 = {50 * 5, 160 * 5, 0};
  Vertex v3 = {70 * 5, 80 * 5, 0};
  render_2dtriangle(v1, v2, v3, &image, red);
  v1 = {180 * 5, 50 * 5, 0};
  v2 = {150 * 5, 1 * 5, 0};
  v3 = {70 * 5, 180 * 5, 0};
  render_2dtriangle(v1, v2, v3, &image, white);
  v1 = {180 * 5, 150 * 5, 0};
  v2 = {120 * 5, 160 * 5, 0};
  v3 = {130 * 5, 180 * 5, 0};
  render_2dtriangle(v1, v2, v3, &image, blue);

  // for (size_t i = 0; i < faces_array.size; i++) {
  //   Face f = faces_array.data[i];
  //   Vertex v1 = vertex_array.data[f.v1];
  //   Vertex v2 = vertex_array.data[f.v2];
  //   Vertex v3 = vertex_array.data[f.v3];
  //   float half_width = (WIDTH - PADDING) / 2.;
  //   float half_height = (HEIGHT - PADDING) / 2.;

  //  double x0 = (v1.x + 1.) * half_width;
  //  double x1 = (v2.x + 1.) * half_width;
  //  double y0 = (v1.y + 1.) * half_height + PADDING / 2.f;
  //  double y1 = (v2.y + 1.) * half_height + PADDING / 2.f;

  //  v1 = {x0, y0};
  //  v2 = {x1, y1};

  //  x1 = (v3.x + 1.) * half_width;
  //  y1 = (v3.y + 1.) * half_height + PADDING / 2.f;
  //  v3 = {x1, y1};

  //  render_2dtriangle(v1, v2, v3, &image, white);
  //}

  image.flip_vertically(); // i want to have the origin at the left bottom
                           // corner of the image

  char IMG_Filename[256] = BUILD_DIR;
  strcat_s(IMG_Filename, "output.tga");
  image.write_tga_file(IMG_Filename);

  // FREEEEEEEEEEE
  vertex_array_free(&vertex_array);
  faces_array_free(&faces_array);

  return 0;
}

#include <string.h>

#include <stdio.h>

#include "faces_array.h"
#include "geometry.h"
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
const int WIDTH = 2000;
const int HEIGHT = 2000;
const int PADDING = 15;

int main(int argc, char **argv) {
  printf("Render start...\n");

  TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

  // Handle triangles
  dynVertexArray vertex_array;
  vertex_array_init(&vertex_array);
  FacesArray faces_array = faces_array_init();

  // Handle texture
  TGAImage texture;
  texture.read_tga_file("./data/african_head_diffuse.tga");
  dynVertexArray texture_coords;
  vertex_array_init(&texture_coords);

  parse_obj("./data/head.obj", &vertex_array, &faces_array, &texture_coords);

  Vec3f light_dir = {0, 0, -1};
  Vertex screen_coords[3];
  Vertex texture_vertices[3];

  // Allocate for depth
  Zbuffer zbuf;
  init_zbuffer(&zbuf, WIDTH, HEIGHT);

  Matrix44f viewport = {
      0.707107, 0,        -0.707107, 0, -0.331295, 0.883452, -0.331295, 0,
      0.624695, 0.468521, 0.624695,  0, 4.000574,  3.00043,  4.000574,  1};
  //to_identity(&viewport);
  invert_it(&viewport);
  print_matrix(&viewport);

  Vec3f p1 = {0.5, -0.5};
  Vec3f p1T;
  Vec3f p2 = {0.3, -0.8};
  Vec3f p2T;
  Vec3f p3 = {-0.2, 0.6};
  Vec3f p3T;
  render_line(p1T, p2T, green, &image);
  render_line(p2T, p3T, red, &image);
  render_line(p3T, p1T, blue, &image);

  // for (size_t i = 0; i < faces_array.size; i++) {
  //   Face f = faces_array.data[i];

  //  // World coords
  //  Vertex v1 = vertex_array.data[f.v1];
  //  Vertex v2 = vertex_array.data[f.v2];
  //  Vertex v3 = vertex_array.data[f.v3];

  //  texture_vertices[0] = texture_coords.data[f.vt1];
  //  texture_vertices[1] = texture_coords.data[f.vt2];
  //  texture_vertices[2] = texture_coords.data[f.vt3];

  //  // ilumination intensity
  //  Vec3f ab = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
  //  Vec3f ac = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
  //  Vec3f normal = cross_product(ac, ab);
  //  normalize(&normal);
  //  double intensity = dot_product(normal, light_dir);

  //  // Calculate screen coordinates
  //  double half_width = (WIDTH - PADDING) / 2.;
  //  double half_height = (HEIGHT - PADDING) / 2.;
  //  screen_coords[0] = {(v1.x + 1.) * half_width,
  //                      (v1.y + 1.) * half_height + PADDING / 2.f};
  //  screen_coords[1] = {(v2.x + 1.) * half_width,
  //                      (v2.y + 1.) * half_height + PADDING / 2.f};
  //  screen_coords[2] = {(v3.x + 1.) * half_width,
  //                      (v3.y + 1.) * half_height + PADDING / 2.f};

  //  // Don't draw what's not iluminated
  //  if (intensity > 0) {
  //    render_triangle(screen_coords, texture_vertices, &zbuf, &image,
  //    &texture,
  //                    intensity);
  //  }
  //}

  image.flip_vertically(); // i want to have the origin at the left bottom
                           // corner of the image

  char IMG_Filename[256] = BUILD_DIR;
  strcat_s(IMG_Filename, "output.tga");
  image.write_tga_file(IMG_Filename);

  // FREEEEEEEEEEE
  vertex_array_free(&vertex_array);
  vertex_array_free(&texture_coords);
  faces_array_free(&faces_array);
  free_zbuffer(&zbuf);

  return 0;
}

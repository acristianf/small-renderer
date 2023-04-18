#include "tiny_obj_parser.h"

static void parse_vertex_coord(char buf[], size_t buf_size, int *c, FILE *fptr,
                               double *vpos) {
  for (size_t n = 0; n < buf_size; n++) {
    if (isdigit(*c = fgetc(fptr)) || *c == '-' || *c == '.') {
      buf[n] = *c;
    } else if (*c == 'e') {
      // HANDLE EXPONENTIALS
      buf[n] = '\0';
      *vpos = atof(buf);
      int expcount = 0;
      while ((*c = fgetc(fptr)) != ' ') {
        buf[expcount++] = *c;
      }
      buf[expcount] = '\0';
      *vpos = *vpos * exp(atof(buf));
      return;
    } else {
      buf[n] = '\0';
      break;
    }
  }
  *vpos = atof(buf);
}

static void parse_face_coord(char buf[], size_t buf_size, int *c, FILE *fptr,
                             uint32_t *fpos) {
  for (size_t n = 0; n < buf_size; n++) {
    if (isdigit(*c = fgetc(fptr))) {
      buf[n] = *c;
    } else {
      buf[n] = '\0';
      break;
    }
  }
  // Arrays start at 1 so substract it
  *fpos = atof(buf) - 1;
}

void parse_obj(const char *obj_filepath, dynVertexArray *vertex_array,
               FacesArray *faces_array, dynVertexArray *texture_coords) {
  FILE *fptr;

  if (fopen_s(&fptr, obj_filepath, "rb") != 0) {
    fprintf(stderr, "File error: couldn't open %s", obj_filepath);
    exit(-1);
  };
  printf("Opened file %s..\n", obj_filepath);

  int c;
  char buf[MAX_STRING_BUFFER_SIZE];
      Vertex v = {};
      Face f = {};
  while ((c = fgetc(fptr)) != EOF) {
    if (c == 'v' && (c = fgetc(fptr)) == ' ') {

      parse_vertex_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &v.x);
      parse_vertex_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &v.y);
      parse_vertex_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &v.z);

      vertex_array_append(vertex_array, v);
    } else if (c == 't' && (c = fgetc(fptr) == ' ')) {
      // skip another whitespace
      c = fgetc(fptr);

      parse_vertex_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &v.x);
      parse_vertex_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &v.y);
      parse_vertex_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &v.z);

      vertex_array_append(texture_coords, v);
    } else if (c == 'f' && (c = fgetc(fptr)) == ' ') {

      parse_face_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &f.v1);
      parse_face_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &f.vt1);
      while (c != ' ') {
        c = fgetc(fptr);
      }
      parse_face_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &f.v2);
      parse_face_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &f.vt2);
      while (c != ' ') {
        c = fgetc(fptr);
      }
      parse_face_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &f.v3);
      parse_face_coord(buf, MAX_STRING_BUFFER_SIZE, &c, fptr, &f.vt3);

      faces_array_append(faces_array, f);
    }
  }

  fclose(fptr);
};

#ifndef _TINY_OBJ_PARSER_H
#define _TINY_OBJ_PARSER_H

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "faces_array.h"
#include "vertex_array.h"

void parse_obj(const char *obj_filepath, dynVertexArray *vertex_array,
               FacesArray *faces_array, dynVertexArray *texture_coords);

#endif

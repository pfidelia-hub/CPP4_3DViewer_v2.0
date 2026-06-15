#pragma once

#include "model_parser.h"
#include "model_matrix.h"

#define MODEL_SIZE 300
#define PROJ_COEFF 4

namespace s21 {


enum class Projection_type { PARALLEL = 1, CENTRAL = 2 };

enum class Line_type{
  SOLID = 1,
  DASHED = 2,
};

enum class Vertex_type {
  NONE = 0,
  CIRCLE = 1,
  SQUARE = 2,
};

struct settings_t {
  int projection_type;
  int poligons_type;
  int edges_type;
  float edges_color_r;
  float edges_color_g;
  float edges_color_b;
  int edges_thickness;
  int vertices_type;
  float vertices_color_r;
  float vertices_color_g;
  float vertices_color_b;
  int vertices_size;
  float background_color_r;
  float background_color_g;
  float background_color_b;
  int view_dist;
};

struct affins_data_t {
  int rotate_x;
  int rotate_y;
  int rotate_z;
  int translate_x;
  int translate_y;
  int translate_z;
  int scale;
};


}  // namespace s21


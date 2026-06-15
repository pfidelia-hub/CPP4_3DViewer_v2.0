#pragma once
#include "model_matrix.h"

namespace s21 {

struct match_t {
  bool res;
  int number;
};

struct polygon_t {
  int count_of_vertexes_in_polygon;
  double *number_of_vertex_in_polygon;
};

struct data_from_obj_t {
  int count_of_vertexes;
  int count_of_facets;
  int count_of_edges;
  matrix_t matrix_3d;
  polygon_t *polygons;
  polygon_t *polygons_edges;
  double x_max;
  double x_min;
  double y_max;
  double y_min;
  double z_max;
  double z_min;
  double normalization_ratio;
};

enum class read_file_e { FIRST = 1, SECOND = 2 };

class Parser {
  polygon_t _poligon;

  double normalization(data_from_obj_t *);

 public:
  Parser() : _poligon({0, nullptr}) {}

  void parser(const char *file_name, data_from_obj_t *obj);
  void read_from_file(const char *file_name, data_from_obj_t *object,
                      read_file_e priority);
  void make_matrix_and_polygons(data_from_obj_t *object);
  void cleare_struct_matrix_and_poligons(data_from_obj_t *object);
  int counting_number_of_vertices(char *str);
  void alloc_mem_for_polygon_massiv(data_from_obj_t *object,
                                    int namber_of_polygon);

  data_from_obj_t create_sample(data_from_obj_t *obj);
  void clear_sample(data_from_obj_t *obj);
  void print_model(data_from_obj_t *obj, int pr);

  void edges_count(data_from_obj_t *object);

  void clear_poligon(data_from_obj_t *obj, int namber_of_poligon);
  void find(char *str, char *dest);
};

}  // namespace s21

#include "model_parser.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model_matrix.h"


namespace s21 {

void Parser::parser(const char *file_name, data_from_obj_t *obj) {
  setlocale(LC_NUMERIC, "C");
  read_from_file(file_name, obj, read_file_e::FIRST);
  make_matrix_and_polygons(obj);
  read_from_file(file_name, obj, read_file_e::SECOND);
  obj->count_of_edges = 0;
}

void Parser::read_from_file(const char *file_name, data_from_obj_t *object,
                            read_file_e priority) {
  double x_max = 0.0, x_min = 0.0, y_max = 0.0, y_min = 0.0, z_max = 0.0,
         z_min = 0.0;
  FILE *fl;
  char *fert = NULL;
  char str[256] = {"\0"};
  object->z_max = -100000.0;
  if ((fl = fopen(file_name, "r")) == NULL) {
  } else {
    int row = 1, polig = 1;
    while ((fgets(str, 256, fl)) != NULL) {
      char str1[256];
      char str2[256];
      memcpy(str2, str, 256);
      memcpy(str1, str, 256);
      const char *sep = " \0";
      char *lex2 = strtok_r(str1, sep, &fert);
      if (priority == read_file_e::FIRST) {
        if (*lex2 == 'v') {
          object->count_of_vertexes++;
          double x, y, z;
          sscanf(str, "v %lf %lf %lf", &x, &y, &z);
          x_max = x_max >= x ? x_max : x;
          x_min = x_min <= x ? x_min : x;

          y_max = y_max >= y ? y_max : y;
          y_min = y_min <= y ? y_min : y;

          z_max = z_max >= z ? z_max : z;
          z_min = z_min <= z ? z_min : z;
        }
        if (*lex2 == 'f') object->count_of_facets++;

      } else if (priority == read_file_e::SECOND) {
        if (*lex2 == 'v') {
          int col = 0;
          char *lex = strtok_r(str, sep, &fert);
          while ((lex = strtok_r(NULL, sep, &fert))) {
            object->matrix_3d.matrix[row][col] = atof(lex);
            if (col == 2) {
              if (atof(lex) > object->z_max) object->z_max = atof(lex);
            }
            col++;
          }
          row++;
          memset(str, 0, 255);
          continue;
        }
        if (*lex2 == 'f') {
          const char *sep2 = " ";
          object->polygons[polig].count_of_vertexes_in_polygon =
              counting_number_of_vertices(str);
          alloc_mem_for_polygon_massiv(object, polig);
          int col = 1;
          char lex_f[500];
          char *lex1 = strtok_r(str2, sep2, &fert);
          while ((lex1 = strtok_r(NULL, sep2, &fert))) {
            find(lex1, lex_f);
            object->polygons[polig].number_of_vertex_in_polygon[col] =
                atof(lex_f);
            col++;
          }
          polig++;
          memset(str2, 0, 256);
        }
      }
      memset(str, 0, 256);
    }
    fclose(fl);
    if (priority == read_file_e::FIRST) {
      object->x_max = x_max;
      object->x_min = x_min;
      object->y_max = y_max;
      object->y_min = y_min;
      object->z_max = z_max;
      object->z_min = z_min;
      object->normalization_ratio = normalization(object);
    }
  }
}

void Parser::find(char *str, char *dest) {
  char *f;
  memset(dest, 0, 500);
  if ((f = strchr(str, '/'))) {
    memcpy(dest, str, strlen(str) - strlen(f));
  } else {
    memcpy(dest, str, strlen(str));
  }
}

void Parser::make_matrix_and_polygons(data_from_obj_t *object) {
  object->matrix_3d = s21_create_matrix(object->count_of_vertexes + 1, 3);
  int num = object->count_of_facets + 1;
  object->polygons = new polygon_t[num];
  object->polygons_edges = new polygon_t[num];
}

void Parser::cleare_struct_matrix_and_poligons(data_from_obj_t *object) {
  if (object->matrix_3d.matrix != nullptr) {
    s21_remove_matrix(&object->matrix_3d);
    for (int i = 1; i <= object->count_of_facets; i++) {
      clear_poligon(object, i);
    }
    free(object->polygons);
    free(object->polygons_edges);
  }
  object->count_of_edges = 0;
  object->count_of_facets = 0;
  object->count_of_vertexes = 0;
  object->x_max = 0.0;
  object->x_min = 0.0;
  object->y_max = 0.0;
  object->y_min = 0.0;
  object->z_max = 0.0;
  object->z_min = 0.0;
  object->normalization_ratio = 0.0;
}

void Parser::clear_sample(data_from_obj_t *obj) {
  s21_remove_matrix(&obj->matrix_3d);
  for (int i = 1; i <= obj->count_of_facets; i++) {
    free(obj->polygons[i].number_of_vertex_in_polygon);
  }
  obj->count_of_vertexes = 0;
  obj->count_of_facets = 0;
}

int Parser::counting_number_of_vertices(char *str) {
  char *fert = NULL;
  const char *sep = " ";
  char *lex = strtok_r(str, sep, &fert);
  int count = 0;
  while ((lex = strtok_r(NULL, sep, &fert))) {
    count++;
  }
  return count;
}

void Parser::alloc_mem_for_polygon_massiv(data_from_obj_t *object,
                                          int namber_of_polygon) {
  object->polygons[namber_of_polygon].number_of_vertex_in_polygon =
      (double *)calloc(
          object->polygons[namber_of_polygon].count_of_vertexes_in_polygon + 1,
          sizeof(double));
  object->polygons_edges[namber_of_polygon].number_of_vertex_in_polygon =
      (double *)calloc(
          object->polygons[namber_of_polygon].count_of_vertexes_in_polygon + 1,
          sizeof(double));
}

void Parser::clear_poligon(data_from_obj_t *obj, int namber_of_poligon) {
  free(obj->polygons[namber_of_poligon].number_of_vertex_in_polygon);
  free(obj->polygons_edges[namber_of_poligon].number_of_vertex_in_polygon);
}

double Parser::normalization(data_from_obj_t *obj) {
  double res_max = 0.0;
  double range_x = obj->x_max - obj->x_min;
  double range_y = obj->y_max - obj->y_min;
  double range_z = obj->z_max - obj->z_min;
  res_max = range_x > range_y ? range_x : range_y;
  res_max = res_max > range_z ? res_max : range_z;
  return res_max;
}

}  // namespace s21

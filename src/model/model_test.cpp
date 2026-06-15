#include "model.h"

#include <gtest/gtest.h>

#include "model_coords.h"
#include "model_matrix.h"
#include "model_parser.h"
#include <cstring>

using namespace s21;

s21::data_from_obj_t obj;
s21::Parser Par;


TEST(model_matrix, test1) {
  double d1[9] = {1, 2, 3, 6, 2, 3, 1, 2, 8};
  matrix_t m0 = s21_create_matrix(0, 0);
  matrix_t m1 = s21_create_matrix(3, 3);
  EXPECT_EQ(m1.rows, 3);
  s21_remove_matrix(&m1);
}

TEST(model_parser, test1) {
  std::string file_p("x_data/obj_files/cube_test1.obj");
  Par.parser(file_p.c_str(), &obj);
  EXPECT_EQ(obj.count_of_edges, 0);
  Par.cleare_struct_matrix_and_poligons(&obj);
}

TEST(model_parser, test2) {
  std::string file_p("x_data/obj_files/cube_test.obj");
  Par.parser(file_p.c_str(), &obj);

  double tmp[9][3] = {{0.0, 0.0, 0.0},   {1.0, -1.0, -1.0},  {1.0, -1.0, 1.0},
                      {-1.0, -1.0, 1.0}, {-1.0, -1.0, -1.0}, {1.0, 1.0, -1.0},
                      {1.0, 1.0, 1.0},   {-1.0, 1.0, 1.0},   {-1.0, 1.0, -1.0}};
  int pol[8][5] = {{0, 0, 0, 0, 0}, {0, 5, 6, 7, 8}, {0, 1, 2, 3, 4},
                   {0, 1, 5},       {0, 2, 6},       {0, 3, 7},
                   {0, 4, 8},       {0, 2, 3, 4}};

  EXPECT_EQ(obj.count_of_facets, 7);
  EXPECT_EQ(obj.count_of_vertexes, 8);

  for (int i = 1; i <= obj.count_of_facets; i++) {
    for (int j = 1; j <= obj.polygons[i].count_of_vertexes_in_polygon; j++) {
      EXPECT_EQ(obj.polygons[i].number_of_vertex_in_polygon[j], pol[i][j]);
    }
  }
  Par.cleare_struct_matrix_and_poligons(&obj);
}

TEST(model_coords, test1) {
  std::string file_p("x_data/obj_files/cube_test.obj");
  Par.parser(file_p.c_str(), &obj);

  matrix_t transformed;
  matrix_t expected = s21_create_matrix(1, 4);
  matrix_t affins_data_test;
  s21::settings_t settings_test;
  s21::affins_data_t affins_data;
  s21::Projection_type pr_type;
  int res = 0;

  obj.matrix_3d.matrix[0][0] = obj.matrix_3d.matrix[0][1] =
      obj.matrix_3d.matrix[0][2] = 10;
  assign_matrix(&expected, 30.0, 40.0, 50.0, 1.0);

  affins_data.rotate_x = 360;
  affins_data.rotate_y = 360;
  affins_data.rotate_z = 360;
  affins_data.translate_x = 10;
  affins_data.translate_y = 20;
  affins_data.translate_z = 30;
  affins_data.scale = 200;
  Par.cleare_struct_matrix_and_poligons(&obj);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#pragma once
#include "oglwidget.h"

class Controller;
namespace s21 {
class Model;
}

namespace s21 {

class ListBuilder {
  MainWindow *_view;

 public:
  explicit ListBuilder(MainWindow *view) : _view(view) {}

  s21::Model *get_model();

  // --------------------------------------conversion
  // function---------------------------//
  void scale(GLfloat, GLfloat, GLfloat);
  void translate(GLfloat, GLfloat, GLfloat);
  void rotate(GLfloat, GLfloat, GLfloat, GLfloat);
  void rotate_mouse(GLfloat, GLfloat);
  //  --------------------------------------make lists
  // function---------------------------//
  void make_initializing_list();
  void make_model_poligon_list();
  void make_model_vertices_list();
  void make_model_edges_list();
  void make_conversion_list(oper, GLfloat, GLfloat, GLfloat, GLfloat);
  void make_conversion_list_mouse(oper, GLfloat, GLfloat, GLfloat, GLfloat,
                                  GLfloat);
  void make_settings_list();
};

}  //  namespace s21

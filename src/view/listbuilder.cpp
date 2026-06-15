#include "listbuilder.h"

#include "controller/controller.h"
#include "model/model.h"
#include "oglwidget.h"

namespace s21 {

s21::Model* ListBuilder::get_model() {
  return _view->get_controller()->_model;
}

void ListBuilder::scale(GLfloat x, GLfloat y, GLfloat z) {
  make_conversion_list(oper::SCALE, x, y, z, 0.0);
}

void ListBuilder::translate(GLfloat x, GLfloat y, GLfloat z) {
  make_conversion_list(oper::TRANSLATE, x, y, z, 0.0);
}

void ListBuilder::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  make_conversion_list(oper::ROTATE, x, y, z, angle);
}

void ListBuilder::rotate_mouse(GLfloat angle_x, GLfloat angle_y) {
  make_conversion_list_mouse(oper::ROTATE, 0.0, 0.0, 0.0, angle_x, angle_y);
}

void ListBuilder::make_initializing_list() {
  *_view->get_init_list() = glGenLists(1);
  glNewList(*_view->get_init_list(), GL_COMPILE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (_view->get_controller()->_settings->projection_type == 1) {
    gluPerspective(45, 1.0, 1.0, _view->get_back_frustrum());
  } else if (_view->get_controller()->_settings->projection_type == 2) {
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, _view->get_back_frustrum());
  }
  gluLookAt(
      0.0, 0.0,
      _view->get_z_max() / get_model()->get_obj_data()->normalization_ratio +
          _view->get_controller()->_settings->view_dist,
      0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glEndList();
}

void ListBuilder::make_model_poligon_list() {
  double rat = get_model()->get_obj_data()->normalization_ratio;

  *_view->get_poligon_list() = glGenLists(2);
  glNewList(*_view->get_poligon_list(), GL_COMPILE);

  size_t n_faces = get_model()->get_obj_data()->count_of_facets;
  GLdouble** v = get_model()->get_obj_data()->matrix_3d.matrix;

  for (size_t i = 1; i <= n_faces; ++i) {
    GLuint count_vertex =
        get_model()->get_obj_data()->polygons[i].count_of_vertexes_in_polygon;
    glColor3f(0.0, 0.0, 1.0);
    if (count_vertex > 4) {
      glBegin(GL_POLYGON);
      for (GLuint j = 1; j <= count_vertex; j++) {
        GLuint f11 = get_model()
                         ->get_obj_data()
                         ->polygons[i]
                         .number_of_vertex_in_polygon[j];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
        glColor3f(2.0, 0.0, 0.0);
      }
      glEnd();
    } else if (count_vertex == 4) {
      glBegin(GL_QUADS);
      for (GLuint j = 1; j <= count_vertex; j++) {
        GLuint f11 = _view->get_controller()
                         ->_model->get_obj_data()
                         ->polygons[i]
                         .number_of_vertex_in_polygon[j];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
        glColor3f(0.0, 1.0, 0.0);
      }
      glEnd();
    } else if (count_vertex == 3) {
      glBegin(GL_TRIANGLES);
      for (GLuint j = 1; j <= count_vertex; j++) {
        GLuint f11 = _view->get_controller()
                         ->_model->get_obj_data()
                         ->polygons[i]
                         .number_of_vertex_in_polygon[j];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
        glColor3f(1.0, 0.0, 0.0);
      }
      glEnd();
    } else if (count_vertex == 2) {
      glBegin(GL_LINES);
      for (GLuint j = 1; j <= count_vertex; j++) {
        GLuint f11 = _view->get_controller()
                         ->_model->get_obj_data()
                         ->polygons[i]
                         .number_of_vertex_in_polygon[j];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
        glColor3f(0.0, 0.0, 1.0);
      }
      glEnd();
    } else if (count_vertex == 1) {
      glBegin(GL_POINTS);
      for (GLuint j = 1; j <= count_vertex; j++) {
        GLuint f11 = _view->get_controller()
                         ->_model->get_obj_data()
                         ->polygons[i]
                         .number_of_vertex_in_polygon[j];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
        glColor3f(3.0, 0.0, 0.0);
      }
      glEnd();
    }
  }
  glEndList();
}

void ListBuilder::make_model_vertices_list() {
  glDeleteLists(*_view->get_vertices_list(), 1);

  double rat = get_model()->get_obj_data()->normalization_ratio;
  GLfloat red = get_model()->_settings.vertices_color_r / 255;
  GLfloat green = get_model()->_settings.vertices_color_g / 255;
  GLfloat blue = get_model()->_settings.vertices_color_b / 255;
  *_view->get_vertices_list() = glGenLists(3);
  glNewList(*_view->get_vertices_list(), GL_COMPILE);

  size_t n_vert = get_model()->get_obj_data()->count_of_vertexes;
  GLdouble** v = get_model()->get_obj_data()->matrix_3d.matrix;

  glPointSize(_view->get_settings()->vertices_size);
  if (_view->get_settings()->vertices_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  glBegin(GL_POINTS);
  for (size_t i = 0; i < n_vert; i++) {
    glColor3f(red, green, blue);
    glVertex3f(v[i][0] / rat, v[i][1] / rat, v[i][2] / rat);
  }
  glEnd();
  glEndList();
}

void ListBuilder::make_model_edges_list() {
  glDeleteLists(*_view->get_edges_list(), 1);

  double rat = get_model()->get_obj_data()->normalization_ratio;
  GLfloat red = get_model()->_settings.edges_color_r / 255;
  GLfloat green = get_model()->_settings.edges_color_g / 255;
  GLfloat blue = get_model()->_settings.edges_color_b / 255;
  *_view->get_edges_list() = glGenLists(4);
  glNewList(*_view->get_edges_list(), GL_COMPILE);

  size_t n_face = get_model()->get_obj_data()->count_of_facets;
  GLdouble** v = get_model()->get_obj_data()->matrix_3d.matrix;

  for (size_t i = 1; i <= n_face; i++) {
    GLuint count_vertex =
        get_model()->get_obj_data()->polygons[i].count_of_vertexes_in_polygon;

    if (_view->get_settings()->edges_type == 2) {
      glEnable(GL_LINE_STIPPLE);
      glEnable(GL_LINE_SMOOTH);
      glLineStipple(1, 0x8101);
    } else {
      glDisable(GL_LINE_STIPPLE);
      glDisable(GL_LINE_SMOOTH);
    }
    glLineWidth(_view->get_settings()->edges_thickness);
    glBegin(GL_LINES);

    glColor3f(red, green, blue);
    for (GLuint j = 1; j <= count_vertex; j++) {
      GLuint f11 = get_model()
                       ->get_obj_data()
                       ->polygons[i]
                       .number_of_vertex_in_polygon[j];
      glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
      if (j != count_vertex) {
        f11 = get_model()
                  ->get_obj_data()
                  ->polygons[i]
                  .number_of_vertex_in_polygon[j + 1];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
      } else {
        f11 = get_model()
                  ->get_obj_data()
                  ->polygons[i]
                  .number_of_vertex_in_polygon[1];
        glVertex3f(v[f11][0] / rat, v[f11][1] / rat, v[f11][2] / rat);
      }
    }
    glEnd();
  }

  glEndList();
}

void ListBuilder::make_conversion_list(oper a, GLfloat x, GLfloat y, GLfloat z,
                                       GLfloat angle) {
  *_view->get_conversion_list() = glGenLists(5);
  glNewList(*_view->get_conversion_list(), GL_COMPILE);

  if (a == oper::SCALE) {
    glScalef(x, y, z);
  } else if (a == oper::NONE) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  } else if (a == oper::TRANSLATE) {
    glTranslatef(x, y, z);
  } else if (a == oper::ROTATE) {
    glRotatef(angle, x, y, z);
  }
  glEndList();
}

void ListBuilder::make_conversion_list_mouse(oper a, GLfloat x, GLfloat y,
                                             GLfloat z, GLfloat angle_x,
                                             GLfloat angle_y) {
  *_view->get_conversion_list_mouse() = glGenLists(6);
  glNewList(*_view->get_conversion_list_mouse(), GL_COMPILE);

  if (a == oper::SCALE) {
    glScalef(x, y, z);
  } else if (a == oper::NONE) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  } else if (a == oper::TRANSLATE) {
    glTranslatef(x, y, z);
  } else if (a == oper::ROTATE) {
    glRotatef(angle_x, 1.0, 0.0, 0.0);
    glRotatef(angle_y, 0.0, 1.0, 0.0);
  }

  glEndList();
}

void ListBuilder::make_settings_list() {
  *_view->get_settings_list() = glGenLists(7);
  glNewList(*_view->get_settings_list(), GL_COMPILE);
  glViewport(0.0, 0.0, 610.0, 580.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (_view->get_controller()->_settings->projection_type == 1) {
    gluPerspective(45, 1.0, 1.0, _view->get_back_frustrum());
  } else if (_view->get_controller()->_settings->projection_type == 2) {
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, _view->get_back_frustrum());
  }
  gluLookAt(
      0.0, 0.0,
      _view->get_z_max() / get_model()->get_obj_data()->normalization_ratio +
          _view->get_controller()->_settings->view_dist,
      0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glEndList();
}

}  //  namespace s21

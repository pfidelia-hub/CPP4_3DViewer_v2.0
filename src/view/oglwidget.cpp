#include "oglwidget.h"

#include <QGLWidget>
#include <QImage>
#include <QObject>
#include <QTimer>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "controller/controller.h"
#include "listbuilder.h"
#include "mainwindow.h"
#include "model/model.h"
#include "model/model_parser.h"

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  resize(571, 531);
}

void OGLWidget::set_init(int x) { init = x; }

void OGLWidget::set_back_frustrum(GLdouble num) { _back_frustrum = num; }

int OGLWidget::get_init() { return init; }

GLdouble OGLWidget::get_back_frustrum() { return _back_frustrum; }

#if FLAG == 99

void OGLWidget::init_texture(GLuint index, QImage &image) {
  image.convertTo(QImage::Format_RGBA8888);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(image.width()),
               GLsizei(image.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
               image.bits());
}

void OGLWidget::init_light() {
  GLfloat light_ambient[] = {0, 0, 0, 0.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[] = {0.0, 0.0, 2.0, 1.0};

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void OGLWidget::key_press_event(QKeyEvent *event) {
  //   if (event->key() == Qt::Key_F) {
  //   }
}

#endif

void OGLWidget::load_obj_in_gl() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLWidget::update_view() { update(); }

void OGLWidget::view_scale(GLdouble ind) {
  _view->get_builder()->scale(ind, ind, ind);
  update();
}

void OGLWidget::translate_left(GLdouble x) {
  _view->get_builder()->translate(x, 0.0, 0.0);
  update();
}

void OGLWidget::translate_up(GLdouble y) {
  _view->get_builder()->translate(0.0, y, 0.0);
  update();
}

void OGLWidget::rotate_right(GLdouble d) {
  _view->get_builder()->rotate(d, 1.0, 0.0, 0.0);
  update();
}

void OGLWidget::rotate_left(GLdouble d) {
  _view->get_builder()->rotate(d, 1.0, 0.0, 0.0);
  update();
}

void OGLWidget::rotate_up(GLdouble d) {
  _view->get_builder()->rotate(d, 0.0, 1.0, 0.0);
  update();
}

void OGLWidget::rotate_down(GLdouble d) {
  _view->get_builder()->rotate(d, 0.0, 1.0, 0.0);
  update();
}

void OGLWidget::rotate_mouse(GLdouble x, GLdouble y) {
  _view->get_builder()->rotate_mouse(x, y);
  update();
}

void OGLWidget::load_model_data() {}

void OGLWidget::set_view(MainWindow *view) { _view = view; }

void OGLWidget::initializeGL() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  init = 1;
}

void OGLWidget::paintGL() {
  if (_view->get_controller()->_model->get_obj_data()->count_of_vertexes != 0) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(
        _view->get_controller()->_model->_settings.background_color_r / 255,
        _view->get_controller()->_model->_settings.background_color_g / 255,
        _view->get_controller()->_model->_settings.background_color_b / 255,
        0.0);

    glCallList(*_view->get_init_list());
    glCallList(*_view->get_settings_list());
    glCallList(*_view->get_conversion_list());
    glCallList(*_view->get_conversion_list_mouse());
    if (_view->get_controller()->_settings->poligons_type == 1) {
      glCallList(*_view->get_poligon_list());
    }
    if (_view->get_controller()->_settings->vertices_type != 0) {
      glCallList(*_view->get_vertices_list());
    }
    if (_view->get_settings()->edges_type != 0) {
      glCallList(*_view->get_edges_list());
    }

    glDeleteLists(*_view->get_init_list(), 1);
    glDeleteLists(*_view->get_conversion_list(), 1);
    glDeleteLists(*_view->get_settings_list(), 1);
    glDeleteLists(*_view->get_conversion_list_mouse(), 1);
  }
}

void OGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (_view->get_controller()->_settings->projection_type == 1) {
    gluPerspective(45, (float)w / h, 1.0, _back_frustrum);
  } else if (_view->get_controller()->_settings->projection_type == 2) {
    glOrtho(0.0, w, 0.0, h, 1.0, _back_frustrum);
  }

  gluLookAt(0.0, 0.0,
            _view->get_z_max() + _view->get_controller()->_settings->view_dist,
            0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

#pragma once
#include <GL/gl.h>
#include <GL/glu.h>

#include <QKeyEvent>
#include <QObject>
#include <QOpenGLWidget>
#include <QSurfaceFormat>

#include "mainwindow.h"

enum class oper { NONE, SCALE, TRANSLATE, ROTATE };

class MainWindow;

class OGLWidget : public QOpenGLWidget {
  Q_OBJECT

  int init = 0;
  GLdouble _back_frustrum = 5.0;

 public:
  explicit OGLWidget(QWidget *parent = nullptr);
  ~OGLWidget() {}

  MainWindow *_view;

  void set_view_pointer(MainWindow *);
  void set_init(int);
  void set_back_frustrum(GLdouble);

  int get_init();
  GLdouble get_back_frustrum();

  void load_textures();
  void init_texture(GLuint, QImage &);
  void init_light();
  void key_press_event(QKeyEvent *);
  void load_obj_in_gl();
  void update_view();

  // --------------------------------------conversion
  // functions---------------------------//
  void view_scale(GLdouble);
  void translate_left(GLdouble);
  void translate_up(GLdouble);
  void rotate_right(GLdouble);
  void rotate_left(GLdouble);
  void rotate_up(GLdouble);
  void rotate_down(GLdouble);
  void rotate_mouse(GLdouble x, GLdouble y);

  void load_model_data();

 public slots:
  void set_view(MainWindow *);

 signals:
  void dadam();

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
};

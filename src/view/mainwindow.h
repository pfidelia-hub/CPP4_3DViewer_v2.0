#pragma once
#include <GL/gl.h>
#include <GL/glu.h>

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <string>

#include "QObject"
#include "gifmaker.h"
#include "model/model_coords.h"
#include "style/style.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class ViewSettings;
class OGLWidget;

namespace s21 {
class Controller;
class ListBuilder;
}  // namespace s21

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  Ui::MainWindow *ui;

  MainWindow(QWidget *parent, s21::Controller *controller);
  ~MainWindow();

  void set_lineEdit(QString);

  s21::Controller *get_controller();
  s21::ListBuilder *get_builder();
  QString get_file_name();
  Style *get_style_pointer();
  OGLWidget *get_view();
  s21::settings_t *get_settings();

  GLuint *get_init_list();
  GLuint *get_poligon_list();
  GLuint *get_edges_list();
  GLuint *get_vertices_list();
  GLuint *get_conversion_list();
  GLuint *get_settings_list();
  GLuint *get_conversion_list_mouse();

  GLdouble get_back_frustrum();

  GLuint get_z_max();
  void set_z_max(GLuint);

  void draw_settings();
  void update_view_settings();

 private slots:
  void save_images();
  void set_style();
  void on_openFile_clicked();
  void on_settings_clicked();
  void draw(int);
  void animation_right();
  void animation_left();

  void on_pushButton_2_plus_clicked();
  void on_pushButton_3_minus_clicked();
  void on_pushButton_to_right_clicked();
  void on_pushButton_to_left_clicked();
  void on_pushButton_to_up_clicked();
  void on_pushButton_to_down_clicked();
  void on_pushButton_rot_right_clicked();
  void on_pushButton_rot_left_clicked();
  void on_pushButton_rot_up_clicked();
  void on_pushButton_rot_down_clicked();
  void on_pushButton_point_zero_clicked();
  void on_checkBox_2_clicked(bool checked);
  void on_checkBox_clicked(bool checked);
  void on_horizontalSlider_valueChanged(int value);

  void on_horizontalSlider_2_valueChanged(int value);

  void on_horizontalSlider_3_valueChanged(int value);

  void on_pushButton_clicked();

  void on_doubleSpinBox_valueChanged(double arg1);

  void on_spinBox_rotate_up_valueChanged(int arg1);

  void on_spinBox_rotate_left_valueChanged(int arg1);

  void on_doubleSpinBox_up_valueChanged(double arg1);

  void on_doubleSpinBox_left_valueChanged(double arg1);

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

 signals:
  void make_gif();

 protected:
  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseMoveEvent(QMouseEvent *);

 private:
  s21::Controller *_controller;
  ViewSettings *_view_settings;
  s21::settings_t *_settings;
  s21::ListBuilder *_builder;
  QTimer *_paint_timer_right;
  QTimer *_paint_timer_left;
  QTimer *timer_save_images;
  GLuint images_for_gif_count;
  s21::GifMaker *_gif_maker;
  Style _style;
  OGLWidget *_draw;
  GLdouble _angle = 10.0;
  GLuint _z_max;
  QPoint _first_pos;
  GLdouble _scale_last;
  GLint _rotate_up_angle_last;
  GLint _rotate_left_angle_last;
  GLdouble _translate_up_last;
  GLdouble _translate_left_last;

  GLuint _draw_init_list = 0;
  GLuint _draw_model_poligon_list = 0;
  GLuint _draw_model_edges_list = 0;
  GLuint _draw_model_vertices_list = 0;
  GLuint _draw_conversion_list = 0;
  GLuint _draw_settings_list = 0;
  GLuint _draw_conversion_list_mouse = 0;
};

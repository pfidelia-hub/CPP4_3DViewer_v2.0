#include "mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QStyleOption>

#include "QFontDatabase"
#include "controller/controller.h"
#include "listbuilder.h"
#include "model/model.h"
#include "model/model_coords.h"
#include "model/model_observer.h"
#include "ui_mainwindow.h"
#include "ui_viewsettings.h"
#include "viewsettings.h"

// namespace Ui {

/*---------------------------------------consructor----------------------------------------------------*/

MainWindow::MainWindow(QWidget* parent, s21::Controller* controller)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _controller(controller),
      _view_settings(nullptr),
      images_for_gif_count(0),
      _gif_maker(nullptr),
      _scale_last(1.0),
      _rotate_up_angle_last(0),
      _rotate_left_angle_last(0),
      _translate_up_last(0.0),
      _translate_left_last(0.0) {
  ui->setupUi(this);
  _controller->set_view(this);
  _settings = _controller->_settings;
  _builder = new s21::ListBuilder(this);
  _view_settings = new ViewSettings(nullptr, this);
  ui->openGLWidget_2->_view = this;
  _draw = ui->openGLWidget_2;

  timer_save_images = new QTimer(this);
  timer_save_images->setInterval(100);
  connect(timer_save_images, SIGNAL(timeout()), this, SLOT(save_images()));

  setWindowTitle("3d Viewer 2.0");
  set_style();

  _paint_timer_right = new QTimer(this);
  _paint_timer_left = new QTimer(this);
  QObject::connect(_paint_timer_right, SIGNAL(timeout()), this,
                   SLOT(animation_right()));
  QObject::connect(_paint_timer_left, SIGNAL(timeout()), this,
                   SLOT(animation_left()));

  QObject::connect(_controller, SIGNAL(draww(int)), this, SLOT(draw(int)));
}

MainWindow::~MainWindow() {
  _view_settings->saveSettingsInFile();
  _view_settings->close();
  delete ui;
}

/*-------------------------------------------public
 * methods------------------------------------------------*/

s21::Controller* MainWindow::get_controller() { return _controller; }

s21::ListBuilder* MainWindow::get_builder() { return _builder; }

void MainWindow::set_lineEdit(QString str) { ui->lineEdit->setText(str); }

QString MainWindow::get_file_name() { return ui->lineEdit->text(); }

Style* MainWindow::get_style_pointer() { return &_style; }

OGLWidget* MainWindow::get_view() { return _draw; }

s21::settings_t* MainWindow::get_settings() { return _settings; }

GLuint* MainWindow::get_init_list() { return &_draw_init_list; }

GLuint* MainWindow::get_poligon_list() { return &_draw_model_poligon_list; }

GLuint* MainWindow::get_edges_list() { return &_draw_model_edges_list; }

GLuint* MainWindow::get_vertices_list() { return &_draw_model_vertices_list; }

GLuint* MainWindow::get_conversion_list() { return &_draw_conversion_list; }

GLuint* MainWindow::get_settings_list() { return &_draw_settings_list; }

GLuint* MainWindow::get_conversion_list_mouse() {
  return &_draw_conversion_list_mouse;
}

GLdouble MainWindow::get_back_frustrum() {
  return ui->openGLWidget_2->get_back_frustrum();
}

GLuint MainWindow::get_z_max() { return _z_max; }

void MainWindow::set_z_max(GLuint z) { _z_max = z; }

void MainWindow::draw_settings() {
  _builder->make_settings_list();
  ui->openGLWidget_2->update_view();
}

void MainWindow::update_view_settings() {
  ui->countOfVertxes->clear();
  ui->countOfVertxes->setText(
      QString::number(_controller->_model->get_obj_data()->count_of_vertexes));
}

void MainWindow::save_images() {
  QString file_name =
      "./save/gif/" + QString::number(images_for_gif_count) + ".jpg";
  ui->openGLWidget_2->grabFramebuffer().save(file_name);
  ui->pushButton_4->setText(QString::number(images_for_gif_count));
  if (images_for_gif_count == 40) {
    timer_save_images->stop();
    ui->pushButton_4->setText("Save GIF");
    if (!_gif_maker) {
      _gif_maker = s21::GifMakerBash::instance();
      _gif_maker->make_gif();
      s21::GifMakerBash::instance_delete();
      system("rm -f ./save/gif/*.jpg");
    }
    images_for_gif_count = 0;
  }
  images_for_gif_count++;
}

/*--------------------------------------------privat
 * slots---------------------------------------------------*/
void MainWindow::set_style() {
  ui->centralwidget->setStyleSheet(Style::set_main_form_style());
  QPushButton{Style::SetPushbuttonStyle()};
}

void MainWindow::on_openFile_clicked() {
  QString file_name = QFileDialog::getOpenFileName(
      this, "File Selection", "./x_data/obj_files", "Images (*.obj)");
  if (!file_name.isEmpty()) {
    ui->lineEdit->setText(QFileInfo(file_name).completeBaseName());
    _controller->set_file(file_name.toStdString());
    _view_settings->saveSettingsInFile();
    _controller->_model->get_observer()->update(s21::observ_e::FILE);
  }
}

void MainWindow::on_settings_clicked() {
  _view_settings->setWindowFlags(Qt::WindowStaysOnTopHint);
  _view_settings->move(440, 400);
  _view_settings->show();
}

void MainWindow::draw(int ind) {
  update_view_settings();
  if (_controller->_model->get_obj_data()->count_of_facets != 0) {
    if (ind == 1) {
      _builder->make_initializing_list();
    }
    _builder->make_model_poligon_list();

    _builder->make_model_vertices_list();

    _builder->make_model_edges_list();

    ui->openGLWidget_2->update_view();
  }
}

void MainWindow::animation_right() { _draw->rotate_up(_angle); }

void MainWindow::animation_left() { _draw->rotate_down(_angle * -1.0); }

void MainWindow::on_pushButton_2_plus_clicked() { ui->doubleSpinBox->stepUp(); }

void MainWindow::on_pushButton_3_minus_clicked() {
  ui->doubleSpinBox->stepDown();
}

void MainWindow::on_pushButton_to_right_clicked() {
  ui->doubleSpinBox_left->stepUp();
}

void MainWindow::on_pushButton_to_left_clicked() {
  ui->doubleSpinBox_left->stepDown();
}

void MainWindow::on_pushButton_to_up_clicked() {
  ui->doubleSpinBox_up->stepUp();
}

void MainWindow::on_pushButton_to_down_clicked() {
  ui->doubleSpinBox_up->stepDown();
}

void MainWindow::on_pushButton_rot_right_clicked() {
  ui->spinBox_rotate_up->stepDown();
}

void MainWindow::on_pushButton_rot_left_clicked() {
  ui->spinBox_rotate_up->stepUp();
}

void MainWindow::on_pushButton_rot_up_clicked() {
  ui->spinBox_rotate_left->stepUp();
}

void MainWindow::on_pushButton_rot_down_clicked() {
  ui->spinBox_rotate_left->stepDown();
}

void MainWindow::on_pushButton_point_zero_clicked() {
  _builder->make_initializing_list();
  ui->openGLWidget_2->update();

  _scale_last = 1.0;
  ui->doubleSpinBox->setValue(1.0);

  _rotate_up_angle_last = 0.0;
  ui->spinBox_rotate_up->setValue(0.0);

  _rotate_left_angle_last = 0.0;
  ui->spinBox_rotate_left->setValue(0.0);

  _translate_up_last = 0.0;
  ui->doubleSpinBox_up->setValue(0.0);

  _translate_left_last = 0.0;
  ui->doubleSpinBox_left->setValue(0.0);
}

void MainWindow::on_checkBox_2_clicked(bool checked) {
  if (checked) {
    ui->checkBox->setChecked(false);
    if (_paint_timer_right->isActive()) {
      _paint_timer_right->stop();
    }
    _paint_timer_left->start();
  } else {
    _paint_timer_left->stop();
  }
}

void MainWindow::on_checkBox_clicked(bool checked) {
  if (checked) {
    ui->checkBox_2->setChecked(false);
    if (_paint_timer_left->isActive()) {
      _paint_timer_left->stop();
    }
    _paint_timer_right->start();
  } else {
    _paint_timer_right->stop();
  }
}

void MainWindow::mousePressEvent(QMouseEvent* mov) { _first_pos = mov->pos(); }

void MainWindow::mouseMoveEvent(QMouseEvent* mov) {
  GLuint x = mov->pos().x();
  GLuint x_f = _first_pos.x();
  GLuint re1_x = x_f - x;

  GLuint y = mov->pos().y();
  GLuint y_f = _first_pos.y();
  GLuint re1_y = y_f - y;
  if (re1_x < 100 && re1_y < 100) {
    ui->openGLWidget_2->rotate_mouse(re1_x, re1_y);
  }
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  _controller->_settings->background_color_r = value;
  ui->label_6->setText(QString::number(value));
  if (_view_settings != nullptr) {
    _view_settings->get_ui()->lineEdit_5->setText(QString::number(value));
  }
  ui->openGLWidget_2->update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  _controller->_settings->background_color_g = value;
  ui->label_7->setText(QString::number(value));
  if (_view_settings != nullptr) {
    _view_settings->get_ui()->lineEdit_6->setText(QString::number(value));
  }
  ui->openGLWidget_2->update();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value) {
  _controller->_settings->background_color_b = value;
  ui->label_8->setText(QString::number(value));
  if (_view_settings != nullptr) {
    _view_settings->get_ui()->lineEdit_7->setText(QString::number(value));
  }
  ui->openGLWidget_2->update();
}

void MainWindow::on_pushButton_clicked() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  ui->openGLWidget_2->update();
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) {
  if (_scale_last != 0.0) {
    ui->openGLWidget_2->view_scale(arg1 / _scale_last);
  } else {
    ui->openGLWidget_2->view_scale(arg1);
  }
  _scale_last = arg1;
}

void MainWindow::on_spinBox_rotate_up_valueChanged(int arg1) {
  ui->openGLWidget_2->rotate_left((arg1 - _rotate_up_angle_last) * -1);
  _rotate_up_angle_last = arg1;
}

void MainWindow::on_spinBox_rotate_left_valueChanged(int arg1) {
  ui->openGLWidget_2->rotate_down(arg1 - _rotate_left_angle_last);
  _rotate_left_angle_last = arg1;
}

void MainWindow::on_doubleSpinBox_up_valueChanged(double arg1) {
  ui->openGLWidget_2->translate_up(arg1 - _translate_up_last);
  _translate_up_last = arg1;
}

void MainWindow::on_doubleSpinBox_left_valueChanged(double arg1) {
  ui->openGLWidget_2->translate_left(arg1 - _translate_left_last);
  _translate_left_last = arg1;
}

void MainWindow::on_pushButton_2_clicked() {
  QString file = QFileDialog::getSaveFileName(this, "Save as...", "save");
  ui->openGLWidget_2->grabFramebuffer().save(file);
}

void MainWindow::on_pushButton_4_clicked() {
  system("mkdir ./save/gif");
  system("rm ./save/gif/*.jpg");
  images_for_gif_count = 0;
  timer_save_images->start();
}

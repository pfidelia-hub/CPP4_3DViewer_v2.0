#include "viewsettings.h"

#include <QLabel>
#include <QObject>

#include "controller/controller.h"
#include "listbuilder.h"
#include "mainwindow.h"
#include "model/model_coords.h"
#include "style/style.h"
#include "ui_mainwindow.h"
#include "ui_viewsettings.h"

ViewSettings::ViewSettings(QWidget *parent, MainWindow *view)
    : QDialog(parent = view), ui(new Ui::ViewSettings), _view(view) {
  ui->setupUi(this);
  _settings = new QSettings("./settings.cfg", QSettings::NativeFormat, this);
  this->move(x() + (view->width() - this->width()) / 2,
             y() + (view->height() - this->height()) / 2);

  connect(this, SIGNAL(update_view(int)), view, SLOT(draw(int)));
  loadSettings();
  set_style();
}

ViewSettings::~ViewSettings() { delete ui; }

Ui::ViewSettings *ViewSettings::get_ui() { return ui; }

void ViewSettings::set_style() {
  this->setStyleSheet(Style::set_main_form_style());

  if (ui->pushButton_central->isChecked()) {
    ui->pushButton_central->setStyleSheet(Style::setPushButtonChecked());
  } else {
    ui->pushButton_central->setStyleSheet(Style::setPushbuttonSettingsStyle());
  }
  if (ui->pushButton_parallel->isChecked()) {
    ui->pushButton_parallel->setStyleSheet(Style::setPushButtonChecked());
  } else {
    ui->pushButton_parallel->setStyleSheet(Style::setPushbuttonSettingsStyle());
  }

  ui->pushButton_parallel->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 20));

  ui->pushButton_central->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 20));

  if (ui->pushButton_5->isChecked() == false) {
    ui->pushButton_5->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_5->setStyleSheet(Style::setPushButtonChecked());
  }

  ui->pushButton_5->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->pushButton->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->pushButton_2->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->pushButton_8->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->pushButton_9->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));

  if (ui->pushButton_6->isChecked() == false) {
    ui->pushButton_6->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_6->setStyleSheet(Style::setPushButtonChecked());
  }

  ui->pushButton_6->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));

  if (ui->pushButton_7->isChecked() == false) {
    ui->pushButton_7->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_7->setStyleSheet(Style::setPushButtonChecked());
  }

  ui->pushButton_7->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));

  if (ui->pushButton_3->isChecked() == false) {
    ui->pushButton_3->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_3->setStyleSheet(Style::setPushButtonChecked());
  }
  ui->pushButton_3->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));

  if (ui->pushButton_edge_dashed->isChecked() == false) {
    ui->pushButton_edge_dashed->setStyleSheet(
        Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_edge_dashed->setStyleSheet(Style::setPushButtonChecked());
  }
  ui->pushButton_edge_dashed->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));

  if (ui->pushButton_edge_solid->isChecked() == false) {
    ui->pushButton_edge_solid->setStyleSheet(
        Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_edge_solid->setStyleSheet(Style::setPushButtonChecked());
  }
  ui->pushButton_edge_solid->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));

  if (ui->pushButton->isChecked() == false) {
    ui->pushButton->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton->setStyleSheet(Style::setPushButtonChecked());
  }
  if (ui->pushButton_2->isChecked() == false) {
    ui->pushButton_2->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_2->setStyleSheet(Style::setPushButtonChecked());
  }
  if (ui->pushButton_8->isChecked() == false) {
    ui->pushButton_8->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_8->setStyleSheet(Style::setPushButtonChecked());
  }
  if (ui->pushButton_9->isChecked() == false) {
    ui->pushButton_9->setStyleSheet(Style::setPushbuttonSettingsStyle());
  } else {
    ui->pushButton_9->setStyleSheet(Style::setPushButtonChecked());
  }

  ui->label->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_2->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_3->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_4->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_5->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_6->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_7->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_8->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_9->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_10->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
  ui->label_11->setFont(
      _view->get_style_pointer()->get_fon(":/resourses/Allstar.ttf", 15));
}

/*-----------------------------------------------------public----------------------------------------*/

void ViewSettings::saveSettingsInFile() {
  _settings->setValue(
      "file", QString::fromStdString(_view->get_controller()->get_file()));
  _settings->setValue("file_base_name", _view->get_file_name());
  _settings->setValue("projection_type",
                      _view->get_settings()->projection_type);
  _settings->setValue("background_color_b",
                      _view->get_settings()->background_color_b);
  _settings->setValue("background_color_g",
                      _view->get_settings()->background_color_g);
  _settings->setValue("background_color_r",
                      _view->get_settings()->background_color_r);
  _settings->setValue("edges_color_b", _view->get_settings()->edges_color_b);
  _settings->setValue("edges_color_g", _view->get_settings()->edges_color_g);
  _settings->setValue("edges_color_r", _view->get_settings()->edges_color_r);
  _settings->setValue("edges_thickness",
                      _view->get_settings()->edges_thickness);
  _settings->setValue("edges_type", _view->get_settings()->edges_type);
  _settings->setValue("poligons_type", _view->get_settings()->poligons_type);
  _settings->setValue("vertices_color_b",
                      _view->get_settings()->vertices_color_b);
  _settings->setValue("vertices_color_g",
                      _view->get_settings()->vertices_color_g);
  _settings->setValue("vertices_color_r",
                      _view->get_settings()->vertices_color_r);
  _settings->setValue("vertices_size", _view->get_settings()->vertices_size);
  _settings->setValue("vertices_type", _view->get_settings()->vertices_type);
  _settings->setValue("view_dist", _view->get_settings()->view_dist);
}

void ViewSettings::loadSettings() {
  s21::settings_t *setting = _view->get_settings();

  _view->set_lineEdit(_settings->value("file_base_name", "").toString());

  _view->get_controller()->set_file(
      _settings->value("file", " ").toString().toStdString());
  setting->projection_type = _settings->value("projection_type", "2").toInt();
  setting->background_color_b =
      _settings->value("background_color_b", "255").toInt();
  setting->background_color_g =
      _settings->value("background_color_g", "255").toInt();
  setting->background_color_r =
      _settings->value("background_color_r", "255").toInt();
  setting->edges_color_b = _settings->value("edges_color_b", "250").toInt();
  setting->edges_color_g = _settings->value("edges_color_g", "0").toInt();
  setting->edges_color_r = _settings->value("edges_color_r", "80").toInt();
  setting->edges_thickness =
      _settings->value("edges_thickness", "0.1").toDouble();
  setting->edges_type = _settings->value("edges_type", "1").toInt();
  setting->poligons_type = _settings->value("poligons_type", "0").toInt();
  setting->vertices_type = _settings->value("vertices_type", "0").toInt();
  setting->vertices_color_b =
      _settings->value("vertices_color_b", "127").toInt();
  setting->vertices_color_g =
      _settings->value("vertices_color_g", "127").toInt();
  setting->vertices_color_r =
      _settings->value("vertices_color_r", "127").toInt();
  setting->vertices_size = _settings->value("vertices_size", "1").toInt();
  setting->view_dist = _settings->value("view_dist", "2").toInt();
  load_to_view_settings();
}

void ViewSettings::load_to_view_settings() {
  s21::settings_t *setting = _view->get_settings();

  _view->ui->label_6->setText(QString::number(setting->background_color_r));
  _view->ui->label_7->setText(QString::number(setting->background_color_g));
  _view->ui->label_8->setText(QString::number(setting->background_color_b));

  _view->ui->horizontalSlider->setValue(setting->background_color_r);
  _view->ui->horizontalSlider_2->setValue(setting->background_color_g);
  _view->ui->horizontalSlider_3->setValue(setting->background_color_b);

  ui->spinBox_vert_r->setValue(setting->vertices_color_r);
  ui->spinBox_vert_g->setValue(setting->vertices_color_g);
  ui->spinBox_vert_b->setValue(setting->vertices_color_b);

  ui->spinBox_edges_r->setValue(setting->edges_color_r);
  ui->spinBox_edges_g->setValue(setting->edges_color_g);
  ui->spinBox_edges_b->setValue(setting->edges_color_b);

  ui->doubleSpinBox->setValue(setting->edges_thickness);

  ui->doubleSpinBox_vert_size->setValue(setting->vertices_size);

  ui->doubleSpinBox_2->setValue(_view->ui->openGLWidget_2->get_back_frustrum());

  if (setting->projection_type == 2) {
    ui->pushButton_parallel->setChecked(true);
  } else if (setting->projection_type == 1) {
    ui->pushButton_central->setChecked(true);
  }

  ui->lineEdit_view_dist->setText(
      QString::number(_view->get_settings()->view_dist));

  ui->lineEdit_5->setText(QString::number(setting->background_color_r));
  ui->lineEdit_6->setText(QString::number(setting->background_color_g));
  ui->lineEdit_7->setText(QString::number(setting->background_color_b));

  if (setting->vertices_type == 0) {
    ui->pushButton_5->setChecked(true);
  } else if (setting->vertices_type == 1) {
    ui->pushButton_6->setChecked(true);
  } else if (setting->vertices_type == 2) {
    ui->pushButton_7->setChecked(true);
  }

  if (setting->edges_type == 0) {
    ui->pushButton_3->setChecked(true);
  } else if (setting->edges_type == 1) {
    ui->pushButton_edge_solid->setChecked(true);
  } else if (setting->edges_type == 2) {
    ui->pushButton_edge_dashed->setChecked(true);
  }

  if (setting->poligons_type == 0) {
    ui->pushButton->setChecked(true);
  } else if (setting->poligons_type == 1) {
    ui->pushButton_2->setChecked(true);
  } else if (setting->poligons_type == 2) {
    ui->pushButton_8->setChecked(true);
  } else if (setting->poligons_type == 3) {
    ui->pushButton_9->setChecked(true);
  }

  set_style();
}

void ViewSettings::set_view(MainWindow *view) { _view = view; }

void ViewSettings::on_buttonBox_accepted() {
  saveSettingsInFile();
  _view->draw_settings();
}

void ViewSettings::on_pushButton_parallel_clicked(bool checked) {
  if (checked) {
    ui->pushButton_parallel->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_central->setChecked(false);
    ui->pushButton_central->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->projection_type = 2;
    _view->draw_settings();
  }
}

void ViewSettings::on_pushButton_central_clicked(bool checked) {
  if (checked) {
    ui->pushButton_central->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_parallel->setChecked(false);
    ui->pushButton_parallel->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->projection_type = 1;
    _view->draw_settings();
  }
}

void ViewSettings::on_pushButton_5_clicked(bool checked) {
  if (checked) {
    ui->pushButton_5->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_6->setChecked(false);
    ui->pushButton_6->setStyleSheet(Style::setPushbuttonSettingsStyle());
    ui->pushButton_7->setChecked(false);
    ui->pushButton_7->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->vertices_type = 0;
    update_view(0);
  }
}

void ViewSettings::on_pushButton_6_clicked(bool checked) {
  if (checked) {
    ui->pushButton_6->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_5->setChecked(false);
    ui->pushButton_5->setStyleSheet(Style::setPushbuttonSettingsStyle());
    ui->pushButton_7->setChecked(false);
    ui->pushButton_7->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->vertices_type = 1;
    update_view(0);
  }
}

void ViewSettings::on_pushButton_7_clicked(bool checked) {
  if (checked) {
    ui->pushButton_7->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_6->setChecked(false);
    ui->pushButton_6->setStyleSheet(Style::setPushbuttonSettingsStyle());
    ui->pushButton_5->setChecked(false);
    ui->pushButton_5->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->vertices_type = 2;
    update_view(0);
  }
}

void ViewSettings::on_pushButton_3_clicked(bool checked) {
  if (checked) {
    ui->pushButton_3->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_edge_dashed->setStyleSheet(
        Style::setPushbuttonSettingsStyle());
    ui->pushButton_edge_solid->setStyleSheet(
        Style::setPushbuttonSettingsStyle());
    _view->get_settings()->edges_type = 0;
    update_view(0);
  }
}

void ViewSettings::on_lineEdit_view_dist_textEdited(const QString &arg1) {
  _view->get_settings()->view_dist = arg1.toInt();
}

void ViewSettings::on_lineEdit_5_textEdited(const QString &arg1) {
  _view->get_settings()->background_color_r = arg1.toFloat();
  _view->ui->horizontalSlider->setValue(arg1.toInt());
  _view->draw_settings();
}

void ViewSettings::on_lineEdit_6_textEdited(const QString &arg1) {
  _view->get_settings()->background_color_g = arg1.toFloat();
  _view->ui->horizontalSlider_2->setValue(arg1.toInt());
  _view->draw_settings();
}

void ViewSettings::on_lineEdit_7_textEdited(const QString &arg1) {
  _view->get_settings()->background_color_b = arg1.toFloat();
  _view->ui->horizontalSlider_3->setValue(arg1.toInt());
  _view->draw_settings();
}

void ViewSettings::on_pushButton_clicked(bool checked) {
  if (checked) {
    ui->pushButton->setChecked(true);
    _view->get_settings()->poligons_type = 0;
    set_style();
    _view->get_view()->update();
  }
}

void ViewSettings::on_pushButton_2_clicked(bool checked) {
  if (checked) {
    ui->pushButton_2->setChecked(true);
    _view->get_settings()->poligons_type = 1;
    set_style();
    _view->get_view()->update();
  }
}

void ViewSettings::on_pushButton_8_clicked(bool checked) {
  if (checked) {
    ui->pushButton_8->setChecked(true);
    _view->get_settings()->poligons_type = 2;
    set_style();
  }
}

void ViewSettings::on_pushButton_9_clicked(bool checked) {
  if (checked) {
    ui->pushButton_9->setChecked(true);
    _view->get_settings()->poligons_type = 3;
    set_style();
  }
}

void ViewSettings::on_spinBox_vert_b_valueChanged(int arg1) {
  _view->get_settings()->vertices_color_b = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_vertice_list();
  }
}

void ViewSettings::on_spinBox_vert_g_valueChanged(int arg1) {
  _view->get_settings()->vertices_color_g = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_vertice_list();
  }
}

void ViewSettings::on_spinBox_vert_r_valueChanged(int arg1) {
  _view->get_settings()->vertices_color_r = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_vertice_list();
  }
}

void ViewSettings::remake_vertice_list() {
  _view->get_builder()->make_model_vertices_list();
  update_view(0);
}

void ViewSettings::remake_edges_list() {
  _view->get_builder()->make_model_edges_list();
  update_view(0);
}

void ViewSettings::on_doubleSpinBox_vert_size_valueChanged(double arg1) {
  _view->get_settings()->vertices_size = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_vertice_list();
  }
}

void ViewSettings::on_pushButton_edge_solid_clicked(bool checked) {
  if (checked) {
    ui->pushButton_edge_solid->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_edge_dashed->setStyleSheet(
        Style::setPushbuttonSettingsStyle());
    ui->pushButton_3->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->edges_type = 1;
    update_view(0);
  }
}

void ViewSettings::on_pushButton_edge_dashed_clicked(bool checked) {
  if (checked) {
    ui->pushButton_edge_dashed->setStyleSheet(Style::setPushButtonChecked());
    ui->pushButton_edge_solid->setStyleSheet(
        Style::setPushbuttonSettingsStyle());
    ui->pushButton_3->setStyleSheet(Style::setPushbuttonSettingsStyle());
    _view->get_settings()->edges_type = 2;
    update_view(0);
  }
}

void ViewSettings::on_spinBox_edges_r_valueChanged(int arg1) {
  _view->get_settings()->edges_color_r = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_edges_list();
  }
}

void ViewSettings::on_spinBox_edges_g_valueChanged(int arg1) {
  _view->get_settings()->edges_color_g = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_edges_list();
  }
}

void ViewSettings::on_spinBox_edges_b_valueChanged(int arg1) {
  _view->get_settings()->edges_color_b = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_edges_list();
  }
}

void ViewSettings::on_doubleSpinBox_valueChanged(double arg1) {
  _view->get_settings()->edges_thickness = arg1;
  if (_view->ui->openGLWidget_2->get_init() == 1) {
    remake_edges_list();
  }
}

void ViewSettings::on_doubleSpinBox_2_valueChanged(double arg1) {
  _view->ui->openGLWidget_2->set_back_frustrum(arg1);
}

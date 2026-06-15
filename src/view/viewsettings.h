#pragma once

#include <QDialog>
#include <QSettings>

#include "style/style.h"

namespace s21 {
class Controller;
}
// QT_BEGIN_NAMESPACE
namespace Ui {
class ViewSettings;
}
// QT_END_NAMESPACE
class MainWindow;

class ViewSettings : public QDialog {
  Q_OBJECT

 public:
  explicit ViewSettings(QWidget *parent, MainWindow *view);
  ~ViewSettings();

  Ui::ViewSettings *get_ui();
  void set_view(MainWindow *view);

  void saveSettingsInFile();
  void loadSettings();
  void load_to_view_settings();

 private slots:

  void on_buttonBox_accepted();
  void set_style();
  void on_pushButton_parallel_clicked(bool checked);
  void on_pushButton_central_clicked(bool checked);
  void on_pushButton_5_clicked(bool checked);
  void on_pushButton_6_clicked(bool checked);
  void on_pushButton_7_clicked(bool checked);
  void on_pushButton_3_clicked(bool checked);

  void on_lineEdit_view_dist_textEdited(const QString &arg1);

  void on_lineEdit_5_textEdited(const QString &arg1);

  void on_lineEdit_6_textEdited(const QString &arg1);

  void on_lineEdit_7_textEdited(const QString &arg1);

  void on_pushButton_clicked(bool checked);

  void on_pushButton_2_clicked(bool checked);

  void on_pushButton_8_clicked(bool checked);

  void on_pushButton_9_clicked(bool checked);

  void on_spinBox_vert_b_valueChanged(int arg1);

  void on_spinBox_vert_g_valueChanged(int arg1);

  void on_spinBox_vert_r_valueChanged(int arg1);

  void on_doubleSpinBox_vert_size_valueChanged(double arg1);

  void on_pushButton_edge_solid_clicked(bool checked);

  void on_pushButton_edge_dashed_clicked(bool checked);

  void on_spinBox_edges_r_valueChanged(int arg1);

  void on_spinBox_edges_g_valueChanged(int arg1);

  void on_spinBox_edges_b_valueChanged(int arg1);

  void on_doubleSpinBox_valueChanged(double arg1);

  void on_doubleSpinBox_2_valueChanged(double arg1);

 private:
  Ui::ViewSettings *ui;
  QSettings *_settings;
  MainWindow *_view;

  QString split_file_name(QString *str);
  void remake_vertice_list();
  void remake_edges_list();

 signals:
  void update_view(int);
};

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewSettings;
class View;
}  // namespace Ui
QT_END_NAMESPACE

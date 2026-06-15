#pragma once
#include <QDialog>
#include <QObject>
#include <string>

#include "model/model_coords.h"

// QT_BEGIN_NAMESPACE
namespace Ui {
class ViewSettings;
}
// QT_END_NAMESPACE

class MainWindow;
namespace s21 {

class Model;

class Controller : public QObject {
  Q_OBJECT

 public:
  MainWindow *_view;
  s21::Model *_model;
  settings_t *_settings;

 public:
  Controller(QObject *parent, Model *model);
  ~Controller();

  void set_view(MainWindow *vi);
  void set_file(std::string file);
  std::string get_file();

  void draw();

 signals:
  void draww(int);
};

}  // namespace s21

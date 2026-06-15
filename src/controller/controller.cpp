#include "controller.h"

#include "model/model.h"
#include "ui_mainwindow.h"
#include "view/mainwindow.h"

namespace s21 {

Controller::Controller(QObject *parent, Model *model)
    : QObject(parent), _view(nullptr), _model(model) {
  _settings = &_model->_settings;
  _model->set_controller(this);
}

Controller::~Controller() {}

void Controller::set_view(MainWindow *vi) { _view = vi; }

void Controller::set_file(std::string file) { _model->set_file_name(file); }

std::string Controller::get_file() { return _model->get_file_name(); }

void Controller::draw() { emit draww(1); }

}  // namespace s21

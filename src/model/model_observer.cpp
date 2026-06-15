#include "model_observer.h"

#include "controller/controller.h"
#include "model.h"
#include "view/mainwindow.h"
#include "view/oglwidget.h"

namespace s21 {

void ModelObserver::update(observ_e observ) {
  if (observ == observ_e::FILE) {
    update_file();
    update_view();
  } else if (observ == observ_e::MODEL) {
    update_view();
  }
}

void ModelObserver::update_view() { _model->get_controller()->draw(); }

void ModelObserver::update_file() {
  _model->start_parsing();
  _model->get_controller()->_view->set_z_max(_model->get_obj_data()->z_max);
}

}  // namespace s21

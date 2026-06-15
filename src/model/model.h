#pragma once
#include <string>

#include "model_coords.h"
#include "model_observer.h"

// namespace s21 {
// class Model;
// }

namespace s21 {

class Controller;

class Model {
 public:
  settings_t _settings;

 public:
  Model();

  void set_file_name(std::string file);
  std::string get_file_name();
  Controller *get_controller();
  data_from_obj_t *get_obj_data();
  Parser *get_parser();
  ModelObserver *get_observer();

  void set_controller(Controller *controller);
  void start_parsing();

 private:
  Controller *_controller{nullptr};  // pointer to controller
  std::string _file_name;            // file for download obj-file
  data_from_obj_t _data_of_model;    // obj data
  affins_data_t _affins_data;        // affins data
  Parser *_parser;
  ModelObserver *_observer;

  #ifdef FLAG
  void notify_observer(observ_e);
  #endif
  void normalize_model(data_from_obj_t *model);
  matrix_t get_affins_data(affins_data_t *affins);
  matrix_t get_transformed_coords(double *vertex, matrix_t *affins_data,
                                  Projection_type pr);

  void init_data_of_model();
};

}  // namespace s21

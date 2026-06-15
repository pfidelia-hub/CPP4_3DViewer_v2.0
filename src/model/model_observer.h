#pragma once

namespace s21 {

enum class observ_e {
    MODEL,
    FILE
};

class Model;


class ModelObserver {
 public:
    explicit ModelObserver(Model *model) : _model(model) {}

    void update(observ_e);

 private:
    Model *_model;

    void update_view();
    void update_file();
};


}  //  namespace s21

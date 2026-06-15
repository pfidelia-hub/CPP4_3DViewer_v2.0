#include "model.h"


namespace s21 {


Model::Model() {
    _parser = new Parser;
    _observer = new ModelObserver(this);
    init_data_of_model();
}

void Model::set_file_name(const std::string file) {
    _file_name = file;
}

std::string Model::get_file_name() {
    return _file_name;
}

Controller *Model::get_controller() {
    return _controller;
}

data_from_obj_t *Model::get_obj_data() {
    return &_data_of_model;
}

Parser* Model::get_parser() {
    return _parser;
}

ModelObserver* Model::get_observer() {
    return _observer;
}

void Model::set_controller(Controller *controller) {
    _controller = controller;
}



void Model::start_parsing() {
    _parser->cleare_struct_matrix_and_poligons(&_data_of_model);
    _parser->parser(_file_name.c_str(), &_data_of_model);
}

void Model::init_data_of_model() {
    _data_of_model.count_of_edges = 0;
    _data_of_model.count_of_facets = 0;
    _data_of_model.count_of_vertexes = 0;
}

#ifdef FLAG
void Model::notify_observer(observ_e observ) {
    _observer->update(observ);
}
#endif

}  // namespace s21

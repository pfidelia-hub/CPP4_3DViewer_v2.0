#include "view/mainwindow.h"
#include "model/model.h"
#include "controller/controller.h"
#include <QApplication>
#include <QObject>
#define FLAG 100

int main(int argc, char *argv[])
{

    QApplication::setOrganizationName("s21");
    QApplication::setApplicationName("3d Viewer 2.0");

    s21::Model model;

    s21::Controller controller(0, &model);

    QApplication a(argc, argv);


    MainWindow wiew(nullptr, &controller);

    wiew.show();

    if(controller._model->get_file_name() != " ") {
        controller._model->get_observer()->update(s21::observ_e::FILE);
    }

    return a.exec();
}

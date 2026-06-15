#include "style.h"






QString Style::set_main_form_style()
{
    return "background-image: url(:/resourses/fon.png)";
}

QString Style::set_settings_form_style()
{
    return "background-image: url(:/resourses/fon4.png)";
}

QString Style::SetPushbuttonStyle()
{
    return "background-color: rgb(131, 42, 255);"
            "color: rgb(158, 250, 255);"
            "border: 3px solid rgb(131, 42, 255);";
}

QString Style::setPushbuttonSettingsStyle()
{
    return "QPushButton{"
           "background: none;"
           "border: 3px solid rgb(131, 42, 255);"
           "border-radius: 10px;"
           "background: qlineargradient(spread:pad, x1:0.476, y1:0, x2:0.487, y2:0.989, stop:0.410526 rgba(254, 190, 255, 255), stop:1 rgba(171, 129, 255, 255));"
            "}";
}

QString Style::setPushButtonChecked()
{
    return "QPushButton{"
            "border: 3px solid rgb(71, 23, 138);"
            "border-radius: 10px;"
            "background: qlineargradient(spread:pad, x1:0.476, y1:0, x2:0.487, y2:0.989, stop:0.410526 rgba(71, 23, 138, 255), stop:1 rgba(171, 129, 255, 255));"
            "}";
}

QString Style::set_Pushbutton_hoover()
{
    return "";
}

Style::Style()
{
//    int id = QFontDatabase::addApplicationFont(":/resourses/Allstar.ttf");
//    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
//    QFont fon(family);
//    _fon = fon;
}

QFont Style::get_fon(QString str, int size)
{
    int id = QFontDatabase::addApplicationFont(str);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont fon(family);
    fon.setPointSize(size);
    return fon;
}



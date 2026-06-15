#pragma once
#include <QString>
#include "QFontDatabase"
#include <QDebug>
#include <QFont>

class Style
{
    QFont _fon;

public:
    static QString set_main_form_style();
    static QString set_settings_form_style();
    static QString SetPushbuttonStyle();
    static QString setPushbuttonSettingsStyle();
    static QString setPushButtonChecked();
    static QString set_Pushbutton_hoover();

    Style();
    QFont get_fon(QString str, int size);

};



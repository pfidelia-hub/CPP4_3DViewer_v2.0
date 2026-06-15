QT       += core gui opengl

LIBS += -lOpenGL -lGLU -lGraphicsMagick++ -lGraphicsMagick


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    main.cpp \
    model/model.cpp \
    model/model_matrix.cpp \
    model/model_observer.cpp \
    model/model_parser.cpp \
    view/gifmaker.cpp \
    view/listbuilder.cpp \
    view/mainwindow.cpp \
    view/oglwidget.cpp \
    view/style/style.cpp \
    view/viewsettings.cpp

HEADERS += \
    controller/controller.h \
    model/model.h \
    model/model_coords.h \
    model/model_matrix.h \
    model/model_observer.h \
    model/model_parser.h \
    view/gifmaker.h \
    view/listbuilder.h \
    view/mainwindow.h \
    view/oglwidget.h \
    view/style/style.h \
    view/viewsettings.h

FORMS += \
    view/mainwindow.ui \
    view/viewsettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    view/resurses.qrc

DISTFILES += \
    view/script/gif.sh

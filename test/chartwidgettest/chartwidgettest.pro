TARGET = chartwidgettest
TEMPLATE = app

QT += core gui
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}

CONFIG += charts
CHARTS += widget

OBJECTS_DIR = tmp
MOC_DIR = tmp

SOURCES += main.cpp \
    mainwidget.cpp

HEADERS += \
    mainwidget.h




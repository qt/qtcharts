include( ../../tests.pri )
QT       += core gui widgets

TARGET = openglseriestest
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp \
        chartview.cpp \
        datasource.cpp

HEADERS  += mainwindow.h \
            chartview.h \
            datasource.h

FORMS    += mainwindow.ui

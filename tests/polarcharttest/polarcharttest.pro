!include( ../tests.pri ) {
    error( "Couldn't find the test.pri file!" )
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polarcharttest
TEMPLATE = app


SOURCES += main.cpp \
            mainwindow.cpp \
            chartview.cpp

HEADERS  += mainwindow.h \
            chartview.h

FORMS    += mainwindow.ui

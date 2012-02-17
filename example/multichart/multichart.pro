!include( ../../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
!include( ../../integrated.pri ) {
    error( "Couldn't find the integrated.pri file !")
}

QT += core gui

TARGET = multichart
TEMPLATE = app

SOURCES += main.cpp \
    multichartwidget.cpp

HEADERS  += \
    multichartwidget.h





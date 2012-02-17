!include( ../../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
!include( ../../integrated.pri ) {
    error( "Couldn't find the integrated.pri file !")
}

QT += core gui

TARGET = piechart
TEMPLATE = app

SOURCES += main.cpp customslice.cpp
HEADERS += customslice.h

OBJECTS_DIR = tmp
MOC_DIR = tmp



!include( ../example.pri ) {
    error( "Couldn't find the example.pri file!" )
}
QT       += core gui

TARGET = scatterinteractions
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

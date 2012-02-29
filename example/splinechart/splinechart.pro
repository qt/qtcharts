#-------------------------------------------------
#
# Project created by QtCreator 2012-02-29T12:37:46
#
#-------------------------------------------------

!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}

QT       += core gui

TARGET = splinechart
TEMPLATE = app


SOURCES += main.cpp\
        splinewidget.cpp

HEADERS  += splinewidget.h

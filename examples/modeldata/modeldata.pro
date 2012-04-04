#-------------------------------------------------
#
# Project created by QtCreator 2012-03-08T14:30:24
#
#-------------------------------------------------

!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

QT       += core gui

TARGET = modeldata
TEMPLATE = app


SOURCES += main.cpp\
        tablewidget.cpp \
    customtablemodel.cpp

HEADERS  += tablewidget.h \
    customtablemodel.h

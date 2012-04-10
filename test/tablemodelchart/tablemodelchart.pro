!include( ../test.pri ) {
    error( "Couldn't find the test.pri file!" )
}

QT       += core gui

TARGET = tablemodelchart
TEMPLATE = app


SOURCES += main.cpp\
        tablewidget.cpp \
    customtablemodel.cpp

HEADERS  += tablewidget.h \
    customtablemodel.h

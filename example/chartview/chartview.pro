!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
QT       += core gui

TARGET = chartview
TEMPLATE = app

SOURCES += main.cpp

!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

QT += core gui

TARGET = chartinteractions
TEMPLATE = app

HEADERS += chart.h chartview.h
SOURCES += main.cpp chart.cpp chartview.cpp

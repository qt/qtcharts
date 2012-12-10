!include( ../tests.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = presenterchart
HEADERS += chartview.h
SOURCES += main.cpp chartview.cpp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

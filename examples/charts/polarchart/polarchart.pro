!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = polarchart
SOURCES += main.cpp chartview.cpp
HEADERS += chartview.h

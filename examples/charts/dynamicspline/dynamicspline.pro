!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = dynamicspline
HEADERS += chart.h
SOURCES += main.cpp chart.cpp

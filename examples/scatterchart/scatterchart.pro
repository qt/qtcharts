!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}
TARGET = scatterchart
SOURCES += main.cpp \
    chartview.cpp

HEADERS += \
    chartview.h

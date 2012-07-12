!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = donut
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

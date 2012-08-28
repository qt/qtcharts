!include( ../demos.pri ) {
 error( "Couldn't find the demos.pri file!" )
}

TARGET = donut
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

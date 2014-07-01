!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = nesteddonuts
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

!include( ../demos.pri ) {
 error( "Couldn't find the demos.pri file!" )
}

TARGET = nesteddonuts
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

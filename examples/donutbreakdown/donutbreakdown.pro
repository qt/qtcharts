!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = donutbreakdown
SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

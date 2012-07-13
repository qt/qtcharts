!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = donutdrilldown
SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = callout
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    callout.cpp

HEADERS  += widget.h \
    callout.h

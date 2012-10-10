!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = legendmarkers
SOURCES += main.cpp \ 
    mainwidget.cpp

HEADERS += \
    mainwidget.h

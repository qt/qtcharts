!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = legend
SOURCES += main.cpp \ 
    mainwidget.cpp

HEADERS += \
    mainwidget.h

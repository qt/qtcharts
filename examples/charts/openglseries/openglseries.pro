!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

TARGET = openglseries
SOURCES += main.cpp \
    datasource.cpp
HEADERS += datasource.h


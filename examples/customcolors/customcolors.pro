!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

TARGET = customcolors
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

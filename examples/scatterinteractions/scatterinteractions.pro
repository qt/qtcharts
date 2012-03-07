!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

TARGET = scatterinteractions
SOURCES += main.cpp\
        mainwindow.cpp
HEADERS  += mainwindow.h

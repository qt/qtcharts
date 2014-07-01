!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = chartthemes
SOURCES = main.cpp themewidget.cpp
HEADERS = themewidget.h

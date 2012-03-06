!include( ../example.pri ) {
    error( "Couldn't find the example.pri file!" )
}
TARGET = scatterchart
SOURCES += main.cpp

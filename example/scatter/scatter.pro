!include( ../example.pri ) {
    error( "Couldn't find the example.pri file!" )
}
TARGET = scatter
SOURCES += main.cpp

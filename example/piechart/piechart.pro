!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
TARGET = piechart
SOURCES += main.cpp customslice.cpp
HEADERS += customslice.h



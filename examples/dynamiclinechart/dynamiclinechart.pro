!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
QT+=opengl
TARGET = dynamiclinechart
SOURCES += main.cpp
HEADERS += wavegenerator.h




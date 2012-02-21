!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
QT+=opengl
TARGET = dynamiclinechart
SOURCES += main.cpp
HEADERS += wavegenerator.h




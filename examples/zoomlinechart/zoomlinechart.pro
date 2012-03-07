!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = zoomlinechart
HEADERS += chartwidget.h
SOURCES += main.cpp chartwidget.cpp





!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
TARGET = zoomlinechart
HEADERS += chartwidget.h
SOURCES += main.cpp chartwidget.cpp





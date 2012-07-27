!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )
TARGET = chartviewer
QT += opengl
SOURCES = main.cpp window.cpp view.cpp     
HEADERS = window.h view.h
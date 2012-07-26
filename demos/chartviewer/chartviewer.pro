!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )
TARGET = chartviewer
QT += opengl
SOURCES = main.cpp chartwindow.cpp
HEADERS = chartwindow.h

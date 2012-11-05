!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )
include(charts/charts.pri)

TARGET = demoLauncher
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )
include(charts/charts.pri)
TARGET = chartviewer
QT += opengl
INCLUDEPATH += .
SOURCES += main.cpp window.cpp view.cpp   
HEADERS += window.h view.h charts.h model.h


include( ../../tests.pri )
include(charts/charts.pri)
TARGET = chartviewer
INCLUDEPATH += .
SOURCES += main.cpp window.cpp view.cpp grid.cpp
HEADERS += window.h view.h charts.h model.h grid.h 


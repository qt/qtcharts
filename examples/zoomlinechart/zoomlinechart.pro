!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = zoomlinechart
HEADERS += chart.h chartview.h
    
SOURCES += main.cpp chart.cpp chartview.cpp

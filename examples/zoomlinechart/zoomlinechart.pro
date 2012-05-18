!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = zoomlinechart
HEADERS += chart.h chartview.h
    
SOURCES += main.cpp chart.cpp chartview.cpp

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_EXAMPLES_BIN_DIR"

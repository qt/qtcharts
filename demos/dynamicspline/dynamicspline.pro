!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )
TARGET = dynamicspline
HEADERS += chart.h
SOURCES += main.cpp chart.cpp

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_DEMOS_BIN_DIR"

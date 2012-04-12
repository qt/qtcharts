!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}
TARGET = scatterchart
SOURCES += main.cpp \
    chartview.cpp

HEADERS += \
    chartview.h

!system:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_EXAMPLES_BIN_DIR"

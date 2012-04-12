!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = piechartdrilldown
SOURCES += main.cpp \
    drilldownslice.cpp \
    drilldownchart.cpp

HEADERS += \
    drilldownchart.h \
    drilldownslice.h

mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_EXAMPLES_BIN_DIR"

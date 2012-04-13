!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = stackedbarchartdrilldown
SOURCES += main.cpp drilldownseries.cpp drilldownchart.cpp
HEADERS += drilldownseries.h drilldownchart.h

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_EXAMPLES_BIN_DIR"

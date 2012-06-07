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

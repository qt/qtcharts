!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = stackedbarchartdrilldown
SOURCES += main.cpp drilldownseries.cpp drilldownchart.cpp
HEADERS += drilldownseries.h drilldownchart.h

!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = donutbreakdown
SOURCES += main.cpp\
    donutbreakdownchart.cpp

HEADERS  += \
    donutbreakdownchart.h

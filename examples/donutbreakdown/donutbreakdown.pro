!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = donutbreakdown
SOURCES += main.cpp\
    donutbreakdownchart.cpp \
    mainslice.cpp

HEADERS  += \
    donutbreakdownchart.h \
    mainslice.h

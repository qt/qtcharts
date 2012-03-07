!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = percentbarchart
SOURCES += main.cpp \
    chartwidget.cpp
HEADERS += \
    chartwidget.h


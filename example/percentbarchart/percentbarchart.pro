!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}

TARGET = percentbarchart
SOURCES += main.cpp \
    chartwidget.cpp
HEADERS += \
    chartwidget.h


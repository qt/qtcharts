!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
TARGET = stackedbarchart
SOURCES += main.cpp \
    chartwidget.cpp
HEADERS += \
    chartwidget.h


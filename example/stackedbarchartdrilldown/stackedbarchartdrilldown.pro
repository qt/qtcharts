!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
TARGET = stackedbarchartdrilldown
SOURCES += main.cpp \
    chartwidget.cpp
HEADERS += \
    chartwidget.h


!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}

TARGET = barchart
SOURCES += main.cpp \
    chartwidget.cpp \
    custombarset.cpp
HEADERS += \
    chartwidget.h \
    custombarset.h


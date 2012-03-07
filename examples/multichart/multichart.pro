!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = multichart
SOURCES += main.cpp \
    multichartwidget.cpp
HEADERS  += \
    multichartwidget.h





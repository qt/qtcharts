!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
TARGET = multichart
SOURCES += main.cpp \
    multichartwidget.cpp
HEADERS  += \
    multichartwidget.h





!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = legend
SOURCES += main.cpp \ 
    mainwidget.cpp

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_EXAMPLES_BIN_DIR"

HEADERS += \
    mainwidget.h

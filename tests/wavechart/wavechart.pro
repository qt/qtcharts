!include( ../tests.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
QT+=opengl
TARGET = wavechart
SOURCES += main.cpp wavechart.cpp
HEADERS += wavechart.h

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_TESTS_BIN_DIR"

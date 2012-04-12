!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = areachart
SOURCES += main.cpp

!system:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_EXAMPLES_BIN_DIR"

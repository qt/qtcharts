!include( ../tests.pri ) {
    error( "Couldn't find the test.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_DEMOS_BIN_DIR"

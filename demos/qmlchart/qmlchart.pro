!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)

mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_DEMOS_BIN_DIR"

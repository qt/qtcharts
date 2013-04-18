!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp

include(../../demos/shared/qmlapplicationviewer/qmlapplicationviewer.pri)

!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)

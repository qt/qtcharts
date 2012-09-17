!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)

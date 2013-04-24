!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp
OTHER_FILES += qml/qmlweather/*

include(qmlapplicationviewer/qmlapplicationviewer.pri)
include(../shared/qmlapplicationviewer/qmlapplicationviewer.pri)


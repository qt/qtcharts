!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp
OTHER_FILES += qml/qmlpolarchart/*

include(../shared/qmlapplicationviewer/qmlapplicationviewer.pri)

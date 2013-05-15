!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp
OTHER_FILES += qml/quick2chart/*

include(qtquick2applicationviewer/qtquick2applicationviewer.pri)


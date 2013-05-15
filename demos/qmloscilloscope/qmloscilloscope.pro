!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

QT += opengl
RESOURCES += resources.qrc
SOURCES += main.cpp \
    datasource.cpp
OTHER_FILES += qml/qmloscilloscope/*

include(qmlapplicationviewer/qmlapplicationviewer.pri)

HEADERS += \
    datasource.h

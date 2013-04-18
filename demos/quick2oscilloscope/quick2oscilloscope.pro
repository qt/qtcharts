!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

QT += opengl
RESOURCES += resources.qrc
SOURCES += main.cpp \
           datasource.cpp
OTHER_FILES += qml/quick2oscilloscope/*

include(../shared/qtquick2applicationviewer/qtquick2applicationviewer.pri)

HEADERS += \
    datasource.h

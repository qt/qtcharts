!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp \
           datasource.cpp
OTHER_FILES += qml/qmloscilloscope/*

HEADERS += \
    datasource.h

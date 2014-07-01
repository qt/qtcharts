!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}
TARGET = datetimeaxis
SOURCES += main.cpp

RESOURCES += \
    sundata.qrc

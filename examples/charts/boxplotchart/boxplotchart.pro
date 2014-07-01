!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = boxplotchart
SOURCES += main.cpp \
    boxdatareader.cpp

RESOURCES += \
    boxplotdata.qrc

HEADERS += \
    boxdatareader.h

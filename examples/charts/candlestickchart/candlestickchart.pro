!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

TARGET = candlestickchart

SOURCES += main.cpp \
    candlestickdatareader.cpp

HEADERS += \
    candlestickdatareader.h

RESOURCES += \
    candlestickdata.qrc

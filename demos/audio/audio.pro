!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )

QT += multimedia

TARGET = audio
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    xyseriesiodevice.cpp

HEADERS  += widget.h \
    xyseriesiodevice.h

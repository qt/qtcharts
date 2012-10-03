!include( ../tests.pri ) {
    error( "Couldn't find the test.pri file!" )
}

QT += core gui
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}

TARGET = uitest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

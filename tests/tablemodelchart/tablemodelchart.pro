!include( ../tests.pri ) {
    error( "Couldn't find the test.pri file!" )
}

QT       += core gui

TARGET = tablemodelchart
TEMPLATE = app


SOURCES += main.cpp\
        tablewidget.cpp \
    customtablemodel.cpp

HEADERS  += tablewidget.h \
    customtablemodel.h

!system_build:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_TESTS_BIN_DIR"

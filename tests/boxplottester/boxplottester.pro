!include( ../tests.pri ) {
    error( "Couldn't find the test.pri file!" )
}

TEMPLATE = app

QT += core gui opengl
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}

SOURCES += main.cpp \
    mainwidget.cpp \
    customtablemodel.cpp

HEADERS += \
    mainwidget.h \
    customtablemodel.h

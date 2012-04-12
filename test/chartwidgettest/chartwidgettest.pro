!include( ../test.pri ) {
    error( "Couldn't find the test.pri file!" )
}

TEMPLATE = app

QT += core gui
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}

SOURCES += main.cpp \
    mainwidget.cpp \
    dataseriedialog.cpp

HEADERS += \
    mainwidget.h \
    dataseriedialog.h

!system:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_TESTS_BIN_DIR"

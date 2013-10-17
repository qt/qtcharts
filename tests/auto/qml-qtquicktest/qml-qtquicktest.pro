!include( ../auto.pri ) {
    error( "Couldn't find the auto.pri file!" )
}

greaterThan(QT_MAJOR_VERSION, 4) {
    TEMPLATE = app
    CONFIG += warn_on qmltestcase
    SOURCES += main.cpp
    OTHER_FILES += tst_*.qml
    DEFINES += QUICK_TEST_SOURCE_DIR=\"\\\"$$PWD\\\"\"
} else {
    error("These auto tests are designed for Qt5 / QtQuick 2.0")
}

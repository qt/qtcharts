!include( ../auto.pri ) {
    error( "Couldn't find the auto.pri file!" )
}

TEMPLATE = app
CONFIG += warn_on qmltestcase
SOURCES += main.cpp
DEFINES += QUICK_TEST_SOURCE_DIR=\"\\\"$$PWD\\\"\"

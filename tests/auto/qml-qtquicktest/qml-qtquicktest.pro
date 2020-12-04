include( ../auto.pri )
TEMPLATE = app
CONFIG += warn_on qmltestcase
CONFIG -= testcase
SOURCES += main.cpp
OTHER_FILES += tst_*.qml
DEFINES += QUICK_TEST_SOURCE_DIR=\"\\\"$$PWD\\\"\"

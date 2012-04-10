!include( ../test.pri ) {
    error( "Couldn't find the test.pri file!" )
}

QT+= sql
TARGET = gdpbarchart
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

!mac {
    FILE = $$PWD/gdpData
    win32:{FILE = $$replace(FILE, "/","\\")}
    # TODO: QMAKE_POST_LINK does not work on mac; how to copy the data file?
    QMAKE_POST_LINK += $$QMAKE_COPY $$FILE $$CHART_BUILD_BIN_DIR
}

!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

QT+= sql
TARGET = gdpbarchart
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

!mac {
    DIR = $$PWD
    
    win32:{DIR = $$replace(DIR, "/","\\")}
    # TODO: QMAKE_POST_LINK does not work on mac; how to copy the data file?
    QMAKE_POST_LINK += $$QMAKE_COPY $$DIR/gdpData $$CHART_BUILD_BIN_DIR
}

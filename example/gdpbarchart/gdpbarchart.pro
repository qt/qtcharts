!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}

QT+= sql
TARGET = gdpbarchart
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

COPY_DATABASE_COMMAND = $$QMAKE_COPY gdpData $$CHART_BUILD_BIN_DIR/gdpData

win32 {
    COPY_DATABASE_COMMAND = $$replace(COPY_DATABASE_COMMAND, "/","\\")
}

QMAKE_POST_LINK = $$COPY_DATABASE_COMMAND

!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}

QT+= sql
TARGET = gdpbarchart
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h
QMAKE_POST_LINK += $$QMAKE_COPY gdpData $$CHART_BUILD_BIN_DIR

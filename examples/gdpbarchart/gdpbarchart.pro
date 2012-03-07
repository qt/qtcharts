!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

QT+= sql
TARGET = gdpbarchart
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h
QMAKE_POST_LINK += $$QMAKE_COPY gdpData $$CHART_BUILD_BIN_DIR

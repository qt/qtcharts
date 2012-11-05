!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )

TARGET = demoLauncher
SOURCES += main.cpp\
        widget.cpp
HEADERS  += widget.h

DEFINES += "BINPATH=$$join($$CHART_BUILD_BIN_DIR, ", ")"

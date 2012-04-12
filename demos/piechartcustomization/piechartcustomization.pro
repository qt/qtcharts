!include( ../demos.pri ) {
 error( "Couldn't find the demos.pri file!" )
}
TARGET = piechartcustomization
SOURCES += main.cpp \
    pentool.cpp \
    brushtool.cpp \
    customslice.cpp \
    mainwidget.cpp

HEADERS += \
    pentool.h \
    brushtool.h \
    customslice.h \
    mainwidget.h

!system:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_DEMOS_BIN_DIR"


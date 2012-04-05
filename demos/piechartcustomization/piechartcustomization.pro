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



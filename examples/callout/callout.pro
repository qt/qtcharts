!include( ../examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

TARGET = callout
TEMPLATE = app

SOURCES += \
        main.cpp\
        callout.cpp \
        view.cpp

HEADERS  += \
        callout.h \
        view.h

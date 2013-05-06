!include( ../../demos/demos.pri ):error( "Couldn't find the demos.pri file!" )

TARGET = demoLauncher
SOURCES += main.cpp\
           widget.cpp \
           graphicsbutton.cpp

HEADERS  += widget.h \
            graphicsbutton.h

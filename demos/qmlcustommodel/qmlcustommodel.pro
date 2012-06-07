!include( ../demos.pri ) {
    error( "Couldn't find the demos.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp\
           customtablemodel.cpp \
           declarativemodel.cpp
HEADERS += customtablemodel.h \
           declarativemodel.h

include(qmlapplicationviewer/qmlapplicationviewer.pri)

TARGET = qtcommercialchartqml
QT += declarative

!include( ../plugins.pri ) {
    error( "Couldn't find the plugins.pri file!" )
}

contains(QT_MAJOR_VERSION, 5) {
    # TODO: QtQuick2 not supported by the implementation currently
    DEFINES += QTQUICK2
}

SOURCES += \
    plugin.cpp \
    declarativechart.cpp \
    declarativexypoint.cpp \
    declarativexyseries.cpp \
    declarativelineseries.cpp \
    declarativesplineseries.cpp \
    declarativeareaseries.cpp \
    declarativescatterseries.cpp \
    declarativepieseries.cpp \
    declarativebarseries.cpp
    
HEADERS += \
    declarativechart.h \
    declarativexypoint.h \
    declarativexyseries.h \
    declarativelineseries.h \
    declarativesplineseries.h \
    declarativeareaseries.h \
    declarativescatterseries.h \
    declarativepieseries.h \
    declarativebarseries.h

TARGETPATH = QtCommercial/Chart
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
qmldir.files += $$PWD/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
INSTALLS += target qmldir

FILE = $$PWD/qmldir
win32:{FILE = $$replace(FILE, "/","\\")}
QMAKE_POST_LINK += $$QMAKE_COPY $$FILE $$CHART_BUILD_PLUGIN_DIR

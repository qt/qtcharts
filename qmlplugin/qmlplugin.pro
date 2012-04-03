TEMPLATE = lib
TARGET = qtcommercialchartqml
CONFIG += qt plugin
QT += declarative

!include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
!include( ../integrated.pri ) {
    error( "Couldn't find the integrated.pri file !")
}

DESTDIR = $$CHART_BUILD_PLUGIN_DIR
contains(QT_MAJOR_VERSION, 5) {
    # TODO: QtQuick2 not supported by the implementation currently
    DEFINES += QTQUICK2
}

OBJECTS_DIR = $$CHART_BUILD_DIR/plugin
MOC_DIR = $$CHART_BUILD_DIR/plugin
UI_DIR = $$CHART_BUILD_DIR/plugin
RCC_DIR = $$CHART_BUILD_DIR/plugin

SOURCES += \
    plugin.cpp \
    declarativechart.cpp \
    declarativexyseries.cpp \
    declarativexypoint.cpp \
    declarativelineseries.cpp \
    declarativesplineseries.cpp \
    declarativeareaseries.cpp \
    declarativescatterseries.cpp \
    declarativepieseries.cpp \
    declarativebarseries.cpp
HEADERS += \
    declarativechart.h \
    declarativexyseries.h \
    declarativexypoint.h \
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

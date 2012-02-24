!include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
!include( ../integrated.pri ) {
    error( "Couldn't find the integrated.pri file !")
}

TEMPLATE = lib
TARGET = qtcommercialchartqml
DESTDIR = $$CHART_BUILD_PLUGIN_DIR
CONFIG += qt plugin
QT += declarative

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
    declarativescatterseries.cpp \
    scatterelement.cpp \
    declarativepieseries.cpp \
    declarativelineseries.cpp
HEADERS += \
    declarativechart.h \
    declarativescatterseries.h \
    scatterelement.h \
    declarativepieseries.h \
    declarativelineseries.h

QMAKE_POST_LINK = $$QMAKE_COPY qmldir $$CHART_BUILD_PLUGIN_DIR

TARGETPATH = QtCommercial/Chart
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
qmldir.files += $$PWD/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmldir

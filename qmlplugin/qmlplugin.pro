!include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
!include( ../integrated.pri ) {
    error( "Couldn't find the integrated.pri file !")
}

TEMPLATE = lib
TARGET = qtcommercialchartqml

CONFIG += qt plugin
QT += declarative

contains(QT_MAJOR_VERSION, 5) {
    # TODO: QtQuick2 not supported by the implementation currently
    DEFINES += QTQUICK2
}

OBJECTS_DIR = $$CHART_BUILD_DIR/lib
MOC_DIR = $$CHART_BUILD_DIR/lib
UI_DIR = $$CHART_BUILD_DIR/lib
RCC_DIR = $$CHART_BUILD_DIR/lib

SOURCES += \
    plugin.cpp \
    declarativechart.cpp \
    declarativeseries.cpp
HEADERS += \
    declarativechart.h \
    declarativeseries.h

TARGETPATH = QtCommercial/Chart
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
qmldir.files += $$PWD/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmldir



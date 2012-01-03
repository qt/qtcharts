TEMPLATE = lib
TARGET = qmlchartplugin

CONFIG += qt plugin
QT += declarative

contains(QT_MAJOR_VERSION, 5) {
    DEFINES += QTQUICK2
}

OBJECTS_DIR = tmp
MOC_DIR = tmp

SOURCES += \
    plugin.cpp \
    declarativechart.cpp
HEADERS += \
    declarativechart.h
include(../src/chart.pri)

TARGETPATH = com/digia/charts

#DESTDIR = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmldir.files += $$PWD/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmldir


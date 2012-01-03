TARGET = ChartWidget
TEMPLATE = lib

QT += core gui
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}

SOURCES += \
    chartwidget.cpp
HEADERS += \
    chartwidget.h
include(../src/chart.pri)

OBJECTS_DIR = tmp
MOC_DIR = tmp

DEFINES += CHARTWIDGET_LIBRARY

public_headers.path = $$[QT_INSTALL_HEADERS]/Charts
public_headers.files = chartwidget.h

target.path=$$[QT_INSTALL_LIBS]

INSTALLS += target public_headers

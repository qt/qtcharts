include($$OUT_PWD/../../src/charts/qtcharts-config.pri)
QT_FOR_CONFIG += charts

TARGET = qtchartsqml2
CXX_MODULE = charts
DEFINES += QT_BUILD_QMLCHARTS_LIB

QT += opengl qml quick
QT += charts charts-private
QT_PRIVATE += core-private charts-private
contains(QT_COORD_TYPE, float): DEFINES += QT_QREAL_IS_FLOAT

include($$PWD/designer/designer.pri)

SOURCES += \
    chartsqml2_plugin.cpp \
    declarativechart.cpp \
    declarativexypoint.cpp \
    declarativexyseries.cpp \
    declarativecategoryaxis.cpp \
    declarativemargins.cpp \
    declarativeaxes.cpp \
    declarativepolarchart.cpp \
    declarativechartnode.cpp

PRIVATE_HEADERS += \
    declarativechart_p.h \
    declarativexypoint_p.h \
    declarativexyseries_p.h \
    declarativecategoryaxis_p.h \
    declarativemargins_p.h \
    declarativeaxes_p.h \
    declarativepolarchart_p.h \
    declarativeabstractrendernode_p.h \
    declarativechartnode_p.h \
    declarativechartglobal_p.h

contains(QT_CONFIG, opengl) {
    SOURCES += declarativeopenglrendernode.cpp
    PRIVATE_HEADERS += declarativeopenglrendernode_p.h
}
qtConfig(charts-line-chart) {
    SOURCES += declarativelineseries.cpp
    PRIVATE_HEADERS += declarativelineseries_p.h
}
qtConfig(charts-spline-chart) {
    SOURCES += declarativesplineseries.cpp
    PRIVATE_HEADERS += declarativesplineseries_p.h
}
qtConfig(charts-area-chart) {
    SOURCES += declarativeareaseries.cpp
    PRIVATE_HEADERS += declarativeareaseries_p.h
}
qtConfig(charts-scatter-chart) {
    SOURCES += declarativescatterseries.cpp
    PRIVATE_HEADERS += declarativescatterseries_p.h
}
qtConfig(charts-pie-chart) {
    SOURCES += declarativepieseries.cpp
    PRIVATE_HEADERS += declarativepieseries_p.h
}
qtConfig(charts-bar-chart) {
    SOURCES += declarativebarseries.cpp
    PRIVATE_HEADERS += declarativebarseries_p.h
}
qtConfig(charts-boxplot-chart) {
    SOURCES += declarativeboxplotseries.cpp
    PRIVATE_HEADERS += declarativeboxplotseries_p.h
}
qtConfig(charts-candlestick-chart) {
    SOURCES += declarativecandlestickseries.cpp
    PRIVATE_HEADERS += declarativecandlestickseries_p.h
}

HEADERS += $$PRIVATE_HEADERS
INCLUDEPATH += $$PWD

IMPORT_VERSION = 2.$$QT_MINOR_VERSION
QMAKE_QMLPLUGINDUMP_FLAGS = -qapp

load(qml_plugin)

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Charts (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Charts QML plugin for Qt."
}

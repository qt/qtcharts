include($$OUT_PWD/../../src/charts/qtcharts-config.pri)
QT_FOR_CONFIG += charts

TARGET = qtchartsqml2
CXX_MODULE = charts
DEFINES += QT_BUILD_QMLCHARTS_LIB

QT += opengl qml quick
QT += charts charts-private
QT_PRIVATE += core-private charts-private

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

HEADERS += \
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

qtConfig(opengl) {
    SOURCES += declarativeopenglrendernode.cpp
    HEADERS += declarativeopenglrendernode_p.h
}
qtConfig(charts-line-chart) {
    SOURCES += declarativelineseries.cpp
    HEADERS += declarativelineseries_p.h
}
qtConfig(charts-spline-chart) {
    SOURCES += declarativesplineseries.cpp
    HEADERS += declarativesplineseries_p.h
}
qtConfig(charts-area-chart) {
    SOURCES += declarativeareaseries.cpp
    HEADERS += declarativeareaseries_p.h
}
qtConfig(charts-scatter-chart) {
    SOURCES += declarativescatterseries.cpp
    HEADERS += declarativescatterseries_p.h
}
qtConfig(charts-pie-chart) {
    SOURCES += declarativepieseries.cpp
    HEADERS += declarativepieseries_p.h
}
qtConfig(charts-bar-chart) {
    SOURCES += declarativebarseries.cpp
    HEADERS += declarativebarseries_p.h
}
qtConfig(charts-boxplot-chart) {
    SOURCES += declarativeboxplotseries.cpp
    HEADERS += declarativeboxplotseries_p.h
}
qtConfig(charts-candlestick-chart) {
    SOURCES += declarativecandlestickseries.cpp
    HEADERS += declarativecandlestickseries_p.h
}

INCLUDEPATH += $$PWD

IMPORT_VERSION = 2.$$QT_MINOR_VERSION
QMAKE_QMLPLUGINDUMP_FLAGS = -qapp

load(qml_plugin)

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Charts (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Charts QML plugin for Qt."
}

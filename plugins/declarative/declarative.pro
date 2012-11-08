!include( ../plugins.pri ) {
    error( "Couldn't find the plugins.pri file!" )
}

TARGET = qtcommercialchartqml
QT += declarative
DESTDIR = $$CHART_BUILD_QML_PLUGIN_DIR
INCLUDEPATH += $$CHART_BUILD_PRIVATE_HEADER_DIR

CONFIG(debug, debug|release) {
  mac: TARGET = $$join(TARGET,,,_debug)
  win32: TARGET = $$join(TARGET,,,d)
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
    declarativebarseries.cpp \
    declarativecategoryaxis.cpp \
    declarativemargins.cpp

HEADERS += \
    declarativechart.h \
    declarativexypoint.h \
    declarativexyseries.h \
    declarativelineseries.h \
    declarativesplineseries.h \
    declarativeareaseries.h \
    declarativescatterseries.h \
    declarativepieseries.h \
    declarativebarseries.h \
    declarativecategoryaxis.h \
    declarativemargins.h

TARGETPATH = QtCommercial/Chart
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
qmldir.files += $$PWD/qmldir
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
INSTALLS += target qmldir

FILE = $$PWD/qmldir
win32:{FILE = $$replace(FILE, "/","\\")}
QMAKE_POST_LINK += $$QMAKE_COPY $$FILE $$CHART_BUILD_QML_PLUGIN_DIR

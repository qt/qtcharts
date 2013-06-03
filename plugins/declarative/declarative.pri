!include( ../plugins.pri ) {
    error( "Couldn't find the plugins.pri file!" )
}

contains(DEFINES, CHARTS_FOR_QUICK2) {
    DESTDIR = $$CHART_BUILD_QML2_PLUGIN_DIR
} else {
    DESTDIR = $$CHART_BUILD_QML_PLUGIN_DIR
}

INCLUDEPATH += $$CHART_BUILD_PRIVATE_HEADER_DIR

CONFIG(debug, debug|release) {
  mac: TARGET = $$join(TARGET,,,_debug)
  win32: TARGET = $$join(TARGET,,,d)
}

SOURCES += \
    ../declarative/plugin.cpp \
    ../declarative/declarativechart.cpp \
    ../declarative/declarativexypoint.cpp \
    ../declarative/declarativexyseries.cpp \
    ../declarative/declarativelineseries.cpp \
    ../declarative/declarativesplineseries.cpp \
    ../declarative/declarativeareaseries.cpp \
    ../declarative/declarativescatterseries.cpp \
    ../declarative/declarativepieseries.cpp \
    ../declarative/declarativebarseries.cpp \
    ../declarative/declarativecategoryaxis.cpp \
    ../declarative/declarativemargins.cpp \
    ../declarative/declarativeaxes.cpp \
    ../declarative/declarativepolarchart.cpp \
    ../declarative/declarativeboxplotseries.cpp

HEADERS += \
    ../declarative/declarativechart.h \
    ../declarative/declarativexypoint.h \
    ../declarative/declarativexyseries.h \
    ../declarative/declarativelineseries.h \
    ../declarative/declarativesplineseries.h \
    ../declarative/declarativeareaseries.h \
    ../declarative/declarativescatterseries.h \
    ../declarative/declarativepieseries.h \
    ../declarative/declarativebarseries.h \
    ../declarative/declarativecategoryaxis.h \
    ../declarative/declarativemargins.h \
    ../declarative/declarativeaxes.h \
    ../declarative/declarativepolarchart.h \
    ../declarative/shared_defines.h \
    ../declarative/declarativeboxplotseries.h

TARGETPATH = QtCommercial/Chart
target.path = $$IMPORT_INSTALL_PATH/$$TARGETPATH
qmldir.files += $$_PRO_FILE_PWD_/qmldir
qmldir.path +=  $$IMPORT_INSTALL_PATH/$$TARGETPATH
INSTALLS += target qmldir

QMLDIR_FILE = $$_PRO_FILE_PWD_/qmldir
win32:QMLDIR_FILE = $$replace(QMLDIR_FILE, "/","\\")
QMAKE_POST_LINK += $$QMAKE_COPY $$QMLDIR_FILE $$DESTDIR

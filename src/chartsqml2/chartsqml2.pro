
TARGET = qtchartsqml2
QT += qml quick
QT += charts charts-private
TARGETPATH = QtCharts

IMPORT_VERSION = $$MODULE_VERSION

# Only build qml plugin static if Qt itself is also built static
!contains(QT_CONFIG, static): CONFIG -= static staticlib

include($$PWD/designer/designer.pri)

INCLUDEPATH += ../../include \
               ../../include/QtCharts \
               ../charts \
               ../charts/animations \
               ../charts/axis \
               ../charts/domain

SOURCES += \
    chartsqml2_plugin.cpp \
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
    declarativemargins.cpp \
    declarativeaxes.cpp \
    declarativepolarchart.cpp \
    declarativeboxplotseries.cpp

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
    declarativemargins.h \
    declarativeaxes.h \
    declarativepolarchart.h \
    declarativeboxplotseries.h

OTHER_FILES = qmldir

CONFIG += no_cxx_module

load(qml_plugin)

# Copy qmldir to DESTDIR so we can use the plugin directly from there in our examples
# without having to do 'make install'.
!android:!ios {
    copy_qmldir.target = $$DESTDIR/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

QML_FILES += \
    $$PWD/plugins.qmltypes

include( ../../common.pri )
include( ../../integrated.pri )

TARGET = chartwidgettest
TEMPLATE = app

QT += core gui
contains(QT_MAJOR_VERSION, 5) {
    QT += widgets
}


OBJECTS_DIR = tmp
MOC_DIR = tmp

SOURCES += main.cpp \
    mainwidget.cpp \
#    qscatterseries.cpp \
#    qseriespointgraphicsitem.cpp \
    dataseriedialog.cpp

HEADERS += \
    mainwidget.h \
#    qscatterseries.h \
#    qseriespointgraphicsitem.h \
    dataseriedialog.h


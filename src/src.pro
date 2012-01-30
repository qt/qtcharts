!include( ../common.pri ) {
error( Couldn't find the common.pri file! )
}

TARGET = QtCommercialChart
DESTDIR = $$CHART_BUILD_LIB_DIR
TEMPLATE = lib
QT += core \
    gui

CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QtCommercialChartd

SOURCES += \
    barchart/barchartseries.cpp \
    barchart/bargroup.cpp \
    barchart/bar.cpp \
    barchart/stackedbarchartseries.cpp \
    barchart/stackedbargroup.cpp \
    barchart/percentbarchartseries.cpp \
    barchart/percentbargroup.cpp \
    xylinechart/qxychartseries.cpp \
    xylinechart/xylinechartitem.cpp \
    plotdomain.cpp \
    qscatterseries.cpp \
    qpieseries.cpp \
    qchart.cpp \
    axisitem.cpp \
    qchartwidget.cpp \
    pieslice.cpp \
    qchartview.cpp \
    qchartseries.cpp \
    qchartaxis.cpp

PRIVATE_HEADERS += \ 
    xylinechart/xylinechartitem_p.h \
    plotdomain_p.h \  
    qscatterseries_p.h \
    pieslice.h \
    axisitem_p.h \
    chartitem_p.h
    
PUBLIC_HEADERS += \
    qchartseries.h \
    qscatterseries.h \
    qpieseries.h \
    qchart.h \
    qchartwidget.h \
    qchartglobal.h \
    xylinechart/qxychartseries.h \
    barchart/barchartseries.h \
    barchart/bargroup.h \
    barchart/stackedbarchartseries.h \
    barchart/stackedbargroup.h \
    barchart/percentbarchartseries.h \
    barchart/percentbargroup.h \
    qchartview.h \
    qchartaxis.h 
   
HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS

INCLUDEPATH += xylinechart \
               barchart \
               .

OBJECTS_DIR = $$CHART_BUILD_DIR/lib
MOC_DIR = $$CHART_BUILD_DIR/lib
UI_DIR = $$CHART_BUILD_DIR/lib
RCC_DIR = $$CHART_BUILD_DIR/lib


DEFINES += QTCOMMERCIALCHART_LIBRARY

public_headers.path = $$[QT_INSTALL_HEADERS]/QtCommercialChart
public_headers.files = $$PUBLIC_HEADERS
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target \
    public_headers


install_build_headers.name = bild_headers
install_build_headers.output = $$CHART_BUILD_HEADER_DIR/${QMAKE_FILE_BASE}.h
install_build_headers.input = PUBLIC_HEADERS
install_build_headers.commands = $$QMAKE_COPY ${QMAKE_FILE_NAME} $$CHART_BUILD_HEADER_DIR
install_build_headers.CONFIG += target_predeps no_link
QMAKE_EXTRA_COMPILERS += install_build_headers

chartversion.target = qchartversion_p.h
chartversion.commands = @echo "build_time" > $$chartversion.target;
chartversion.depends = $$HEADERS $$SOURCES
PRE_TARGETDEPS += qchartversion_p.h
QMAKE_CLEAN+= qchartversion_p.h
QMAKE_EXTRA_TARGETS += chartversion

unix:QMAKE_DISTCLEAN += -r $$CHART_BUILD_HEADER_DIR $$CHART_BUILD_LIB_DIR
win32:QMAKE_DISTCLEAN += /Q $$CHART_BUILD_HEADER_DIR $$CHART_BUILD_LIB_DIR



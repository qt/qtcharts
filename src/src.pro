TARGET = QtCommercialChart
TEMPLATE = lib
QT += core \
    gui
CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QtCommercialChartd

SOURCES += \ 
    xylinechart/qxychartseries.cpp \
    xylinechart/xylinechartitem.cpp \
    xylinechart/xygrid.cpp \
    xylinechart/xyplotdomain.cpp \
    qscatterseries.cpp \
    qchart.cpp \
    axis.cpp \
    qchartwidget.cpp \
    qchartdata.cpp

PRIVATE_HEADERS += \ 
    xylinechart/xylinechartitem_p.h \
    xylinechart/xyplotdomain_p.h \  
    xylinechart/xygrid_p.h \
    qscatterseries_p.h \
    axis_p.h
    
PUBLIC_HEADERS += \
    qchartseries.h \
    qscatterseries.h \
    qchart.h \
    qchartdata.h \
    qchartwidget.h \
    qchartglobal.h \
    xylinechart/qxychartseries.h

HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS

INCLUDEPATH += xylinechart \
               .

OBJECTS_DIR = ../build/lib
MOC_DIR = ../build/lib
UI_DIR = ../build/lib
RCC_DIR = ../build/lib
DEFINES += QTCOMMERCIALCHART_LIBRARY

public_headers.path = $$[QT_INSTALL_HEADERS]/QtCommercialChart
public_headers.files = $$PUBLIC_HEADERS
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target \
    public_headers

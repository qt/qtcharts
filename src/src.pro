TARGET = QChart
TEMPLATE = lib
QT += core \
    gui
CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QChartd

SOURCES += \ 
    xylinechart/qxychartseries.cpp \
    xylinechart/xylinechartitem.cpp \
    xylinechart/xygrid.cpp \
    xylinechart/xyplotdata.cpp \
    qchart.cpp \
    axis.cpp \
    qchartwidget.cpp

PRIVATE_HEADERS += \ 
    xylinechart/xylinechartitem_p.h \
    xylinechart/xyplotdata_p.h \# to be removed  
    xylinechart/xygrid_p.h \
    axis_p.h
    
PUBLIC_HEADERS += \
    qchartseries.h \
    qchart.h \
    qchartwidget.h \
    qchartconfig.h \ 
    xylinechart/qxychartseries.h 
   
HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS

INCLUDEPATH += xylinechart \
               .

OBJECTS_DIR = ../build/lib
MOC_DIR = ../build/lib
UI_DIR = ../build/lib
RCC_DIR = ../build/lib
DEFINES += QCHART_LIBRARY

public_headers.path = $$[QT_INSTALL_HEADERS]/QCharts
public_headers.files = $$PUBLIC_HEADERS
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target \
    public_headers

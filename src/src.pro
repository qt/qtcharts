TARGET = QChart
TEMPLATE = lib
QT += core \
    gui
CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QChartd
SOURCES += \ 
    xylinechart/qchartwidget.cpp \
    xylinechart/qchart.cpp \
    xylinechart/qxyseries.cpp \
    xylinechart/axis.cpp \
    xylinechart/xylinechart.cpp \
    xylinechart/xygrid.cpp \
    xylinechart/xyplotdata.cpp 

PRIVATE_HEADERS += \ 
    xylinechart/xylinechart_p.h \
    xylinechart/axis_p.h \
    xylinechart/xygrid_p.h \
    xylinechart/xyplotdata_p.h
    
PUBLIC_HEADERS += \
    xylinechart/qchart.h \
    xylinechart/qxyseries.h \
    xylinechart/qchartwidget.h \
    qchartconfig.h 
    
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

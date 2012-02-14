!include( ../common.pri ):error( Couldn't find the common.pri file! )
TARGET = QtCommercialChart
DESTDIR = $$CHART_BUILD_LIB_DIR
TEMPLATE = lib
QT += core \
    gui
CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QtCommercialChartd
SOURCES += barchart/barchartseries.cpp \
    barchart/bargroup.cpp \
    barchart/bar.cpp \
    barchart/stackedbarchartseries.cpp \
    barchart/stackedbargroup.cpp \
    barchart/percentbarchartseries.cpp \
    barchart/percentbargroup.cpp \
    barchart/barlabel.cpp \
    barchart/barchartmodel.cpp \
    barchart/separator.cpp \
    barchart/bargroupbase.cpp \
    barchart/qbarset.cpp \
    barchart/qbarcategory.cpp \
    linechart/linechartanimationitem.cpp \
    linechart/linechartitem.cpp \
    linechart/qlinechartseries.cpp \
    qscatterseries.cpp \
    #scatterpresentation.cpp \
    qchart.cpp \
    axisitem.cpp \
    qchartview.cpp \
    qchartseries.cpp \
    qchartaxis.cpp \
    charttheme.cpp \
    chartdataset.cpp \
    chartpresenter.cpp \
    domain.cpp \
    scatterpresenter.cpp
PRIVATE_HEADERS += linechart/linechartitem_p.h \
    linechart/linechartanimationitem_p.h \
    barchart/barlabel_p.h \
    barchart/bar_p.h \
    barchart/separator_p.h \
    barchart/barchartmodel_p.h \
    qscatterseries_p.h \
    #scatterpresentation.h \
    axisitem_p.h \
    chartitem_p.h \
    charttheme_p.h \
    chartdataset_p.h \
    chartpresenter_p.h \
    domain_p.h
PUBLIC_HEADERS += linechart/qlinechartseries.h \
    barchart/barchartseries.h \
    barchart/bargroup.h \
    barchart/stackedbarchartseries.h \
    barchart/stackedbargroup.h \
    barchart/percentbarchartseries.h \
    barchart/percentbargroup.h \
    barchart/bargroupbase.h \
    barchart/qbarset.h \
    barchart/qbarcategory.h \
    qchartseries.h \
    qscatterseries.h \
    qchart.h \
    qchartglobal.h \
    qchartview.h \
    qchartaxis.h
    
include(piechart/piechart.pri)
    
THEMES += themes/chartthemeicy_p.h \
    themes/chartthemegrayscale_p.h \
    themes/chartthemescientific_p.h \
    themes/chartthemevanilla_p.h
HEADERS += $$PUBLIC_HEADERS \
    scatterpresenter.h
HEADERS += $$PRIVATE_HEADERS
HEADERS += $$THEMES
INCLUDEPATH += linechart \
    barchart \
    themes \
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
install_build_headers.commands = $$QMAKE_COPY \
    ${QMAKE_FILE_NAME} \
    $$CHART_BUILD_HEADER_DIR
install_build_headers.CONFIG += target_predeps \
    no_link
QMAKE_EXTRA_COMPILERS += install_build_headers
chartversion.target = qchartversion_p.h
chartversion.commands = @echo \
    "build_time" \
    > \
    $$chartversion.target;
chartversion.depends = $$HEADERS \
    $$SOURCES
PRE_TARGETDEPS += qchartversion_p.h
QMAKE_CLEAN += qchartversion_p.h
QMAKE_EXTRA_TARGETS += chartversion
unix:QMAKE_DISTCLEAN += -r \
    $$CHART_BUILD_HEADER_DIR \
    $$CHART_BUILD_LIB_DIR
win32:QMAKE_DISTCLEAN += /Q \
    $$CHART_BUILD_HEADER_DIR \
    $$CHART_BUILD_LIB_DIR

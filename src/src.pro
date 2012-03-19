!include( ../common.pri ):error( Couldn't find the common.pri file! )
TARGET = QtCommercialChart
DESTDIR = $$CHART_BUILD_LIB_DIR
TEMPLATE = lib
QT += core \
    gui
win32-msvc*: LIBS += User32.lib
CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QtCommercialChartd
SOURCES += \
    chartdataset.cpp \
    chartpresenter.cpp \
    charttheme.cpp \
    domain.cpp \
    qchart.cpp \
    qchartview.cpp \
    qseries.cpp \
    qlegend.cpp \
    legendmarker.cpp \
    chartbackground.cpp
PRIVATE_HEADERS += \
    chartdataset_p.h \
    chartitem_p.h \
    chartpresenter_p.h \
    charttheme_p.h \
    domain_p.h \
    legendmarker_p.h \
    chartbackground_p.h
PUBLIC_HEADERS += \
    qchart.h \
    qchartglobal.h \
    qseries.h \
    qchartview.h \
    qlegend.h 
    
include(animations/animations.pri)    
include(axis/axis.pri)
include(xychart/xychart.pri)
include(linechart/linechart.pri)
include(areachart/areachart.pri)
include(barchart/barchart.pri)
include(piechart/piechart.pri)
include(scatterseries/scatter.pri)
include(splinechart/splinechart.pri)

THEMES += themes/chartthemedefault_p.h \
    themes/chartthemelight_p.h \
    themes/chartthemebluecerulean_p.h \
    themes/chartthemedark_p.h \
    themes/chartthemebrownsand_p.h \
    themes/chartthemebluencs_p.h \
    themes/chartthemeicy_p.h \
    themes/chartthemegrayscale_p.h \
    themes/chartthemescientific_p.h \
    themes/chartthemevanilla_p.h

HEADERS += $$PUBLIC_HEADERS
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

#qt public headers
#this is very primitive and lame parser , TODO: make perl script insted
!exists($$CHART_BUILD_PUBLIC_HEADER_DIR)
{
    system($$QMAKE_MKDIR $$CHART_BUILD_PUBLIC_HEADER_DIR)
}

for(file, PUBLIC_HEADERS) {
    name = $$split(file,'/')
    name = $$last(name)
    class = "$$cat($$file)"
    class = $$find(class,class) 
    !isEmpty(class){
    class = $$split(class,QTCOMMERCIALCHART_EXPORT)
    class = $$member(class,1)
    class = $$split(class,' ')
    class = $$replace(class,' ','')
    class = $$member(class,0)
    win32:{
        command = "echo $${LITERAL_HASH}include \"$$name\" > $$CHART_BUILD_PUBLIC_HEADER_DIR/$$class"
    }else{
        command = "echo \"$${LITERAL_HASH}include \\\"$$name\\\"\" > $$CHART_BUILD_PUBLIC_HEADER_DIR/$$class"
    } 
    PUBLIC_QT_HEADERS += $$CHART_BUILD_PUBLIC_HEADER_DIR/$$class
    system($$command)
    }
}

public_headers.path = $$[QT_INSTALL_HEADERS]/QtCommercialChart
public_headers.files = $$PUBLIC_HEADERS $$PUBLIC_QT_HEADERS

target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target public_headers

install_build_public_headers.name = build_public_headers
install_build_public_headers.output = $$CHART_BUILD_PUBLIC_HEADER_DIR/${QMAKE_FILE_BASE}.h
install_build_public_headers.input = PUBLIC_HEADERS
install_build_public_headers.commands = $$QMAKE_COPY \
    ${QMAKE_FILE_NAME} \
    $$CHART_BUILD_PUBLIC_HEADER_DIR
install_build_public_headers.CONFIG += target_predeps \
    no_link
    
install_build_private_headers.name = buld_private_headers
install_build_private_headers.output = $$CHART_BUILD_PRIVATE_HEADER_DIR/${QMAKE_FILE_BASE}.h
install_build_private_headers.input = PRIVATE_HEADERS
install_build_private_headers.commands = $$QMAKE_COPY \
    ${QMAKE_FILE_NAME} \
    $$CHART_BUILD_PRIVATE_HEADER_DIR
install_build_private_headers.CONFIG += target_predeps \
    no_link
 
QMAKE_EXTRA_COMPILERS += install_build_public_headers \
    install_build_private_headers \
    
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

# treat warnings as errors
win32-msvc*: {
    QMAKE_CXXFLAGS += /WX
} else {
    QMAKE_CXXFLAGS += -Werror
}

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
    $$PWD/chartdataset.cpp \
    $$PWD/chartpresenter.cpp \
    $$PWD/charttheme.cpp \
    $$PWD/domain.cpp \
    $$PWD/qchart.cpp \
    $$PWD/qchartview.cpp \
    $$PWD/qseries.cpp \
    $$PWD/qlegend.cpp \
    $$PWD/legendmarker.cpp \
    $$PWD/legendscrollbutton.cpp \
    $$PWD/chartbackground.cpp \
    $$PWD/chart.cpp
PRIVATE_HEADERS += \
    $$PWD/chartdataset_p.h \
    $$PWD/chartitem_p.h \
    $$PWD/chartpresenter_p.h \
    $$PWD/charttheme_p.h \
    $$PWD/domain_p.h \
    $$PWD/legendmarker_p.h \
    $$PWD/legendscrollbutton_p.h \
    $$PWD/chartbackground_p.h \
    $$PWD/chart_p.h \
    $$PWD/chartconfig_p.h \
    $$PWD/qchart_p.h \
    $$PWD/qchartview_p.h
PUBLIC_HEADERS += \
    $$PWD/qchart.h \
    $$PWD/qchartglobal.h \
    $$PWD/qseries.h \
    $$PWD/qchartview.h \
    $$PWD/qlegend.h 
    
include(animations/animations.pri)    
include(axis/axis.pri)
include(xychart/xychart.pri)
include(linechart/linechart.pri)
include(areachart/areachart.pri)
include(barchart/barchart.pri)
include(piechart/piechart.pri)
include(scatterseries/scatter.pri)
include(splinechart/splinechart.pri)
include(themes/themes.pri)


HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS
HEADERS += $$THEMES
INCLUDEPATH += ../include .
    
OBJECTS_DIR = $$CHART_BUILD_DIR/lib
MOC_DIR = $$CHART_BUILD_DIR/lib
UI_DIR = $$CHART_BUILD_DIR/lib
RCC_DIR = $$CHART_BUILD_DIR/lib
DEFINES += QTCOMMERCIALCHART_LIBRARY

#qt public headers
#this is very primitive and lame parser , TODO: make perl script insted
!exists($$CHART_BUILD_PUBLIC_HEADER_DIR/QChartGlobal)
{
    system($$QMAKE_MKDIR $$CHART_BUILD_PUBLIC_HEADER_DIR)
     win32:{
        command = "echo $${LITERAL_HASH}include \"qchartglobal.h\" > $$CHART_BUILD_PUBLIC_HEADER_DIR/QChartGlobal"
    }else{
        command = "echo \"$${LITERAL_HASH}include \\\"qchartglobal.h\\\"\" > $$CHART_BUILD_PUBLIC_HEADER_DIR/QChartGlobal"
    } 
    system($$command)
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
    

!win32-msvc*: {

    # There is a problem with jom.exe currently. It does not seem to understand QMAKE_EXTRA_TARGETS properly.
    # This is the case at least with shadow builds.
    # http://qt-project.org/wiki/jom

    chartversion.target = $$PWD/qchartversion_p.h

    unix:{
        chartversion.commands = @echo \
            "const char *buildTime = \\\"`date +'%y%m%d%H%M'`\\\" \\; \
             const char *gitHead = \\\"`git rev-parse HEAD`\\\" \\; " \
            > \
            $$chartversion.target;
    }else{
        chartversion.commands = @echo \
            "const char *buildTime = \"%date%_%time%\" ; \
             const char *gitHead = \"unknown\" ; " \
            > \
            $$chartversion.target
    }

    chartversion.depends = $$HEADERS \
        $$SOURCES

    PRE_TARGETDEPS += $$PWD/qchartversion_p.h
    QMAKE_CLEAN += $$PWD/qchartversion_p.h
    QMAKE_EXTRA_TARGETS += chartversion
}

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

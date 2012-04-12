!include( ../config.pri ):error( Couldn't find the config.pri file! )

TARGET = $$LIBRARY_NAME
DESTDIR = $$CHART_BUILD_LIB_DIR
TEMPLATE = lib
QT = core gui

win32-msvc*: LIBS += User32.lib

CONFIG(debug, debug|release) {
     mac: TARGET = $$join(TARGET,,,_debug)
     win32: TARGET = $$join(TARGET,,d)
}
 
LIBS -= -l$$LIBRARY_NAME
 
SOURCES += \
    $$PWD/chartdataset.cpp \
    $$PWD/chartpresenter.cpp \
    $$PWD/charttheme.cpp \
    $$PWD/domain.cpp \
    $$PWD/qchart.cpp \
    $$PWD/qchartview.cpp \
    $$PWD/qabstractseries.cpp \
    $$PWD/chartbackground.cpp \
    $$PWD/chart.cpp \
    $$PWD/scroller.cpp
PRIVATE_HEADERS += \
    $$PWD/chartdataset_p.h \
    $$PWD/chartitem_p.h \
    $$PWD/chartpresenter_p.h \
    $$PWD/charttheme_p.h \
    $$PWD/domain_p.h \
    $$PWD/chartbackground_p.h \
    $$PWD/chart_p.h \
    $$PWD/chartconfig_p.h \
    $$PWD/qchart_p.h \
    $$PWD/qchartview_p.h \
    $$PWD/scroller_p.h \
    $$PWD/qabstractseries_p.h
PUBLIC_HEADERS += \
    $$PWD/qchart.h \
    $$PWD/qchartglobal.h \
    $$PWD/qabstractseries.h \
    $$PWD/qchartview.h
    
include(animations/animations.pri)
include(areachart/areachart.pri)    
include(axis/axis.pri)
include(barchart/barchart.pri)
include(legend/legend.pri)
include(linechart/linechart.pri)
include(piechart/piechart.pri)
include(scatterseries/scatter.pri)
include(splinechart/splinechart.pri)
include(themes/themes.pri)
include(xychart/xychart.pri)

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
    PUBLIC_QT_HEADERS += $$CHART_BUILD_PUBLIC_HEADER_DIR/QChartGlobal
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
    
# There is a problem with jom.exe currently. It does not seem to understand QMAKE_EXTRA_TARGETS properly.
# This is the case at least with shadow builds.
# http://qt-project.org/wiki/jom

development_build:!win32-msvc*:{
    chartversion.target = $$PWD/qchartversion_p.h

    unix:{
        chartversion.commands = @echo \
            \" $${LITERAL_HASH}ifndef QCHARTVERSION_P_H\\n\
            $${LITERAL_HASH}define QCHARTVERSION_P_H\\n\
            const char *buildTime = \\\"`date +'%y%m%d%H%M'`\\\" ; \\n\
            const char *gitHead = \\\"`git rev-parse HEAD`\\\" ; \\n \ 
            $${LITERAL_HASH}endif \"  \
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

    PRE_TARGETDEPS += $$chartversion.target
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

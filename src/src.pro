!include( ../config.pri ):error( "Couldn't find the config.pri file!" )

############################# BUILD CONFIG ######################################

TARGET = $$LIBRARY_NAME
DESTDIR = $$CHART_BUILD_LIB_DIR
TEMPLATE = lib
QT = core gui
DEFINES += QTCOMMERCIALCHART_LIBRARY
win32:CONFIG += create_prl
# treat warnings as errors
win32-msvc*: {
    QMAKE_CXXFLAGS += /WX
} else {
    QMAKE_CXXFLAGS += -Werror 
}

unix:{
  QMAKE_CXXFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
}

############################# DEPEDENCES ########################################

win32-msvc*: LIBS += User32.lib
LIBS -= -l$$LIBRARY_NAME
INCLUDEPATH += ../include .

############################# SOURCES ##########################################
 
SOURCES += \
    $$PWD/chartdataset.cpp \
    $$PWD/chartpresenter.cpp \
    $$PWD/charttheme.cpp \
    $$PWD/domain.cpp \
    $$PWD/qchart.cpp \
    $$PWD/qchartview.cpp \
    $$PWD/qabstractseries.cpp \
    $$PWD/chartbackground.cpp \
    $$PWD/chartelement.cpp \
    $$PWD/scroller.cpp \
    $$PWD/chartlayout.cpp
PRIVATE_HEADERS += \
    $$PWD/chartdataset_p.h \
    $$PWD/chartitem_p.h \
    $$PWD/chartpresenter_p.h \
    $$PWD/charttheme_p.h \
    $$PWD/domain_p.h \
    $$PWD/chartbackground_p.h \
    $$PWD/chartelement_p.h \
    $$PWD/chartconfig_p.h \
    $$PWD/qchart_p.h \
    $$PWD/qchartview_p.h \
    $$PWD/scroller_p.h \
    $$PWD/qabstractseries_p.h \
    $$PWD/chartlayout_p.h

PUBLIC_HEADERS += \
    $$PWD/qchart.h \
    $$PWD/qchartglobal.h \
    $$PWD/qabstractseries.h \
    $$PWD/qchartview.h \
    $$PWD/chartsnamespace.h
    
include(animations/animations.pri)
include(areachart/areachart.pri)    
include(axis/axis.pri)
include(barchart/barchart.pri)
include(legend/legend.pri)
include(linechart/linechart.pri)
include(piechart/piechart.pri)
include(scatterchart/scatter.pri)
include(splinechart/splinechart.pri)
include(themes/themes.pri)
include(xychart/xychart.pri)

HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS
HEADERS += $$THEMES

############################# BUILD PATH ##########################################
    
OBJECTS_DIR = $$CHART_BUILD_DIR/lib
MOC_DIR = $$CHART_BUILD_DIR/lib
UI_DIR = $$CHART_BUILD_DIR/lib
RCC_DIR = $$CHART_BUILD_DIR/lib

############################# PUBLIC HEADERS GENERTOR ##########################################

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

############################# INSTALLERS ##########################################

public_headers.path = $$[QT_INSTALL_HEADERS]/QtCommercialChart
public_headers.files = $$PUBLIC_HEADERS $$PUBLIC_QT_HEADERS
INSTALLS += public_headers

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

win32:{
   bintarget.CONFIG += no_check_exist
   !staticlib: {
      bintarget.files += $$CHART_BUILD_LIB_DIR\\$${TARGET}.dll
   }
   win32-msvc*:CONFIG(debug, debug|release): {
      bintarget.files += $$CHART_BUILD_LIB_DIR\\$${TARGET}.pdb
   }
   bintarget.path = $$[QT_INSTALL_BINS]

   libtarget.CONFIG += no_check_exist
   libtarget.files = $$CHART_BUILD_LIB_DIR\\$${TARGET}.prl
   win32-msvc*: {
      libtarget.files += $$CHART_BUILD_LIB_DIR\\$${TARGET}.lib
   } else {
      libtarget.files += $$CHART_BUILD_LIB_DIR\\lib$${TARGET}.a
   }
   libtarget.path = $$[QT_INSTALL_LIBS]

   DLLDESTDIR = $$CHART_BUILD_BIN_DIR
   INSTALLS += bintarget libtarget
}else{
   target.path=$$[QT_INSTALL_LIBS]
   INSTALLS += target
}

mac: !staticlib: {
    # Update the name (id) of the library on OSX to point to the lib path
    MAC_CHARTS_LIB_NAME = "lib"$$LIBRARY_NAME".1.dylib"
    QMAKE_POST_LINK += "install_name_tool -id $$CHART_BUILD_LIB_DIR"/"$$MAC_CHARTS_LIB_NAME $$CHART_BUILD_LIB_DIR"/"$$MAC_CHARTS_LIB_NAME"

    # Update the name (id) of the installed library on OSX to point to the installation path
    postinstall.path = $$[QT_INSTALL_LIBS]
    postinstall.extra = "install_name_tool -id $$[QT_INSTALL_LIBS]"/"$$MAC_CHARTS_LIB_NAME $$[QT_INSTALL_LIBS]"/"$$MAC_CHARTS_LIB_NAME"
    INSTALLS += postinstall
}

################################ DEVELOPMENT BUILD ##########################################    
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

############################### CLEAN ###########################################

unix:QMAKE_DISTCLEAN += -r \
    $$CHART_BUILD_HEADER_DIR \
    $$CHART_BUILD_LIB_DIR
win32:QMAKE_DISTCLEAN += /Q \
    $$CHART_BUILD_HEADER_DIR \
    $$CHART_BUILD_LIB_DIR

############################## COVERAGE #########################################

unix:coverage:{

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_LDFLAGS += -fprofile-arcs -ftest-coverage

LIBS += -lgcov

QMAKE_CLEAN += $$OBJECTS_DIR/*.gcda $$OBJECTS_DIR/*.gcno $$PWD/*.gcov ../coverage/*.info
QMAKE_EXTRA_TARGETS += preparecoverage gencoverage

preparecoverage.target = prepare_coverage
preparecoverage.depends = all
preparecoverage.commands =  lcov --directory $$OBJECTS_DIR --zerocounters ;\
                            lcov -i -d $$OBJECTS_DIR -c -o ../coverage/base.info -b $$PWD;

gencoverage.target = gen_coverage
gencoverage.depends = all
gencoverage.commands = lcov -d $$OBJECTS_DIR -c -o ../coverage/src.info -b $$PWD;\
                       lcov -e ../coverage/base.info $$PWD/* $$PWD/animations/* $$PWD/areachart/* $$PWD/axis/* $$PWD/barchart/* $$PWD/legend/* $$PWD/linechart/* $$PWD/piechart/* $$PWD/scatterchart/* $$PWD/splinechart/* $$PWD/themes/* $$PWD/xychart/* -o ../coverage/base.info;\
                       lcov -e ../coverage/src.info $$PWD/* $$PWD/animations/* $$PWD/areachart/* $$PWD/axis/* $$PWD/barchart/* $$PWD/legend/* $$PWD/linechart/* $$PWD/piechart/* $$PWD/scatterchart/* $$PWD/splinechart/* $$PWD/themes/* $$PWD/xychart/* -o ../coverage/src.info;\
                       lcov -a ../coverage/base.info -a ../coverage/src.info -o ../coverage/coverage.info;
}


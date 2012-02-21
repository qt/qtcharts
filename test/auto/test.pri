!include( ../../common.pri ) {
 error( "Couldn't find the common.pri file!" )
}

!include( ../../integrated.pri ) {
 error( "Couldn't find the integrated.pri file !")
}

TEMPLATE = app
CONFIG  += qtestlib

DESTDIR = $$CHART_BUILD_BIN_DIR/test
OBJECTS_DIR = $$CHART_BUILD_DIR/test/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/test/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/test/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/test/$$TARGET

!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")


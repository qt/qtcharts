!include( ../test.pri ) {
    error( "Couldn't find the test.pri file!" )
}

CONFIG  += qtestlib
!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")

INCLUDEPATH += ../inc
HEADERS += ../inc/tst_definitions.h

OBJECTS_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET

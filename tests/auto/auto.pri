!include( ../tests.pri ) {
    error( "Couldn't find the tests.pri file!" )
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += testlib
} else {
    CONFIG  += qtestlib
}
!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")

INCLUDEPATH += ../inc
HEADERS += ../inc/tst_definitions.h

OBJECTS_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET

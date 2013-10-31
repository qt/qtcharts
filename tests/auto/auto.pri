!include( ../tests.pri ) {
    error( "Couldn't find the tests.pri file!" )
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += testlib widgets
} else {
    CONFIG  += qtestlib
}
!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")

android {
    # Workaround to fix android deployment, which seems to always look for target in
    # OUT_PWD instead of DESTDIR. Need to override the QMAKE_POST_LINK setting done
    # in tests.pri, as "tst_" was prepended to the target.
    COPY_PARAMETERS = "$$CHART_BUILD_BIN_DIR/lib$${TARGET}.so $$OUT_PWD/lib$${TARGET}.so"
    contains(QMAKE_HOST.os, Windows): COPY_PARAMETERS = $$replace(COPY_PARAMETERS, "/","\\")
    QMAKE_POST_LINK += $$QMAKE_COPY $$COPY_PARAMETERS
}

INCLUDEPATH += ../inc
HEADERS += ../inc/tst_definitions.h

OBJECTS_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/tests/auto/$$TARGET

!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}
!include( ../build.pri ) {
    error( "Couldn't find the build.pri file !")
}

TEMPLATE = app

DESTDIR = $$CHART_BUILD_BIN_DIR/test
OBJECTS_DIR = $$CHART_BUILD_DIR/test/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/test/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/test/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/test/$$TARGET

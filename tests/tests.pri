!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = app

DESTDIR = $$CHART_BUILD_BIN_DIR
OBJECTS_DIR = $$CHART_BUILD_DIR/tests/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/tests/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/tests/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/tests/$$TARGET

# staticlib config causes problems when building executables
staticlib: CONFIG-=staticlib

!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = app

DESTDIR = $$CHART_BUILD_BIN_DIR
OBJECTS_DIR = $$CHART_BUILD_DIR/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/$$TARGET

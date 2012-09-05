!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = lib

CONFIG+= plugin
OBJECTS_DIR = $$CHART_BUILD_DIR/plugins/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/plugins/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/plugins/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/plugins/$$TARGET

# staticlib config causes problems when building executables
staticlib: CONFIG-=staticlib

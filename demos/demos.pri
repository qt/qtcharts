!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

DESTDIR = $$CHART_BUILD_BIN_DIR
OBJECTS_DIR = $$CHART_BUILD_DIR/bin/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/bin/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/bin/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/bin/$$TARGET

TEMPLATE = app
QT += core gui
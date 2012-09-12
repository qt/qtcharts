!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

DESTDIR = $$CHART_BUILD_BIN_DIR
OBJECTS_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/demos/$$TARGET

TEMPLATE = app
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# staticlib config causes problems when building executables
staticlib: CONFIG-=staticlib

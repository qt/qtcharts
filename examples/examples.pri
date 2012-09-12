!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

DESTDIR = $$CHART_BUILD_BIN_DIR
OBJECTS_DIR = $$CHART_BUILD_DIR/examples/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/examples/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/examples/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/examples/$$TARGET

TEMPLATE = app
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# staticlib config causes problems when building executables
staticlib: CONFIG-=staticlib

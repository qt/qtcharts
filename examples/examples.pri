!include( ../common.pri ) {
 error( "Couldn't find the common.pri file!" )
}

!include( ../integrated.pri ) {
 error( "Couldn't find the integrated.pri file !")
}

DESTDIR = $$CHART_BUILD_BIN_DIR
OBJECTS_DIR = $$CHART_BUILD_DIR/bin/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/bin/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/bin/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/bin/$$TARGET

TEMPLATE = app
QT += core gui
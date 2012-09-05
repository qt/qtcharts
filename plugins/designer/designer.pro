!include( ../plugins.pri ) {
    error( "Couldn't find the plugins.pri file!" )
}

TARGET=qtcommercialchartdesigner
DESTDIR = $$CHART_BUILD_DESIGNER_PLUGIN_DIR
CONFIG += designer
HEADERS = qchartsplugin.h
SOURCES = qchartsplugin.cpp
RESOURCES = qchartsplugin.qrc

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
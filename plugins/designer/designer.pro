TARGET=qtcommercialchartdesigner

!include( ../plugins.pri ) {
    error( "Couldn't find the plugins.pri file!" )
}

CONFIG += designer
HEADERS = qchartsplugin.h
SOURCES = qchartsplugin.cpp
RESOURCES = qchartsplugin.qrc

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
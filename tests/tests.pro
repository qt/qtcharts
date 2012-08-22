!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \ 
    auto \
    chartwidgettest \
    qmlchartproperties \
    qmlchartaxis

!linux-arm*: {
    SUBDIRS += \
            wavechart
}

!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    wavechart \
    gdpbarchart \
    tablemodelchart

!win32:{
    SUBDIRS += auto
}

TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    wavechart \
    gdpbarchart \
    tablemodelchart

!win32:{
    SUBDIRS += auto
}

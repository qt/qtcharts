TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    wavechart \
    gdpbarchart

!win32:{
    SUBDIRS += auto
}

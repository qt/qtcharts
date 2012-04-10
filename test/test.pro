TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    wavechart \
    gdpbarchart \
    tablechartmodel

!win32:{
    SUBDIRS += auto
}

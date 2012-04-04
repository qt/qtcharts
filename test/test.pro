TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    wavechart \
    qmlchart

!win32:{
    SUBDIRS += auto
}

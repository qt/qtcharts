TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    wavechart

!win32:{
    SUBDIRS += auto
}

TEMPLATE = subdirs
SUBDIRS += \ 
    chartwidgettest \
    qmlchart

!win32:{
    SUBDIRS += auto
}

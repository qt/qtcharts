!include( ../tests.pri ) {
 error( "Couldn't find the tests.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \
           qchartview \
           qchart \
           qlineseries \ 
           qbarset \
           qbarseries \
           qstackedbarseries \
           qpercentbarseries \
           qpieslice qpieseries \
           qpiemodelmapper \
           qsplineseries \
           qscatterseries \
           qxymodelmapper \
           qbarmodelmapper \
           qhorizontalbarseries \
           qhorizontalstackedbarseries \
           qhorizontalpercentbarseries \
           qvalueaxis \
           qcategoryaxis \
           qbarcategoryaxis \
           domain \
           chartdataset \
           qml

!linux-arm*: {
SUBDIRS += \
           qdatetimeaxis
}




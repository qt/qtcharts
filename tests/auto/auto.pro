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
           chartdataset 

contains(QT_VERSION, ^4\\.[0-7]\\.[0-3]\\s*$) | contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    warning("QtCommercial.Charts QML API requires at least Qt 4.7.4. You are using $${QT_VERSION} so the QML API is disabled.")
} else {

    SUBDIRS += qml
}

!linux-arm*: {
SUBDIRS += \
           qdatetimeaxis
}




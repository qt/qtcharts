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
           qlegend

contains(QT_VERSION, ^4\\.[0-7]\\.[0-3]\\s*$) | contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    warning("QtCommercial.Charts QML API requires at least Qt 4.7.4. You are using $${QT_VERSION} so the QML API is disabled.")
} else {
    SUBDIRS += qml

    # Check if QtQuickTest is installed
    exists($$(QTDIR)/lib/QtQuickTest.lib) {
        SUBDIRS += qml-qtquicktest
    } else {
        exists($$(QTDIR)/lib/libQtQuickTest.dylib) {
            SUBDIRS += qml-qtquicktest
        } else {
            warning("QtQuickTest not found; cannot build QML api unit tests")
        }
    }
}

!linux-arm*: {
    SUBDIRS += \
           qdatetimeaxis
}




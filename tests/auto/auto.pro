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
           qlogvalueaxis \
           qcategoryaxis \
           qbarcategoryaxis \
           domain \
           chartdataset \
           qlegend

contains(QT_VERSION, ^4\\.[0-7]\\.[0-3]\\s*$) | contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    warning("QtCommercial.Charts QML API requires at least Qt 4.7.4. You are using $${QT_VERSION} so the QML API is disabled.")
} else {
    !contains(QT_VERSION, ^5\\..*\\..*$)|qtHaveModule(declarative): SUBDIRS += qml

    # Check if QtQuickTest is installed
    exists($$(QTDIR)/mkspecs/features/qmltestcase.prf){
        SUBDIRS += qml-qtquicktest
    } else {
        warning("QtQuickTest not found; cannot build QML api unit tests")
    }
}

!linux-arm*: {
    SUBDIRS += \
           qdatetimeaxis
}

contains(QT_VERSION, ^5\\..*\\..*$):qtHaveModule(quick) {
    SUBDIRS += quick2
}




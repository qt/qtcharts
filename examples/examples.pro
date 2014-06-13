CURRENTLY_BUILDING_COMPONENTS = "examples"
!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \
           areachart \
           customchart \
           linechart \
           percentbarchart \
           piechart \
           piechartdrilldown \
           scatterchart \
           scatterinteractions \
           splinechart \
           stackedbarchart \
           stackedbarchartdrilldown \
           zoomlinechart \
           modeldata \
           barchart \
           boxplotchart \
           legend \
           barmodelmapper \
           lineandbar \
           horizontalbarchart \
           horizontalstackedbarchart \
           horizontalpercentbarchart \
           donutbreakdown \
           temperaturerecords \
           donutchart \
           multiaxis \
           legendmarkers \
           logvalueaxis \
           polarchart

!contains(QT_VERSION, ^5\\..*\\..*$)|qtHaveModule(declarative) {
    SUBDIRS += qmlboxplot \
           qmlpiechart
}

!linux-arm*: {
SUBDIRS += \
    datetimeaxis
}

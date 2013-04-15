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
           qmlboxplot \
           qmlpiechart \
           lineandbar \
           horizontalbarchart \
           horizontalstackedbarchart \
           horizontalpercentbarchart \
           donutbreakdown \
           temperaturerecords \
           donutchart \
           multiaxis \
           legendmarkers \
           logvalueaxis

!linux-arm*: {
SUBDIRS += \
    datetimeaxis
}

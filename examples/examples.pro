CURRENTLY_BUILDING_COMPONENTS = "examples"
!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \
           areachart \
           #customchart \
           linechart \
           percentbarchart \
           piechart \
           piechartdrilldown \
           presenterchart \
           scatterchart \
           scatterinteractions \
           splinechart \
           stackedbarchart \
           stackedbarchartdrilldown \
           zoomlinechart \
           modeldata \
           groupedbarchart \
           legend \
           barmodelmapper \
           qmlpiechart

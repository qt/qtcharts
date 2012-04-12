!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

!include( ../build.pri ) {
 error( "Couldn't find the build.pri file !")
}

TEMPLATE = subdirs
SUBDIRS += \
           areachart \
           barchart \
           customchart \
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
           modeldata
          
          
          
          
          
          
          
          

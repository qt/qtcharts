TEMPLATE = subdirs
SUBDIRS += areachart \
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
           polarchart \
           piechartcustomization \
           dynamicspline \
           nesteddonuts \
           chartinteractions \
           callout \
           chartthemes

qtHaveModule(quick) {
    SUBDIRS += qmlboxplot \
           qmlpiechart \
           qmlweather \
           qmlf1legends \
           qmlcustomizations \
           qmlaxes \
           qmlcustomlegend \
           qmlpolarchart \
           qmlchart \
           qmloscilloscope
}

qtHaveModule(multimedia) {
    SUBDIRS += audio
} else {
    message("QtMultimedia library not available. Some examples are disabled.")
}

contains(QT_CONFIG, opengl) {
    SUBDIRS += openglseries
} else {
    message("OpenGL not available. Some examples are disabled.")
}

!contains(QT_COORD_TYPE, float): {
SUBDIRS += \
    datetimeaxis
}


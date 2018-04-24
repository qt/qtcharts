include($$OUT_PWD/../../src/charts/qtcharts-config.pri)
QT_FOR_CONFIG += charts
TEMPLATE = subdirs

qtConfig(charts-area-chart) {
    SUBDIRS += areachart
}
qtConfig(charts-line-chart) {
    SUBDIRS += \
        callout \
        chartinteractions \
        customchart \
        linechart \
        lineandbar \
        legendmarkers \
        logvalueaxis \
        modeldata \
        zoomlinechart
}
qtConfig(charts-spline-chart) {
    SUBDIRS += \
        dynamicspline \
        multiaxis \
        splinechart
    qtConfig(charts-area-chart) {
        SUBDIRS += \
            chartthemes \
            polarchart
    }
}
qtConfig(charts-bar-chart) {
    SUBDIRS += \
        barchart \
        barmodelmapper \
        horizontalbarchart \
        horizontalpercentbarchart \
        horizontalstackedbarchart \
        stackedbarchart \
        stackedbarchartdrilldown \
        percentbarchart \
        legend \
        temperaturerecords
}
qtConfig(charts-pie-chart) {
    SUBDIRS += \
        donutchart \
        donutbreakdown \
        nesteddonuts \
        piechart \
        piechartcustomization \
        piechartdrilldown
    qtHaveModule(quick): SUBDIRS += qmlpiechart
}
qtConfig(charts-boxplot-chart) {
    SUBDIRS += boxplotchart
    qtHaveModule(quick): SUBDIRS += qmlboxplot
}
qtConfig(charts-candlestick-chart) {
    SUBDIRS += candlestickchart
    qtHaveModule(quick): SUBDIRS += qmlcandlestick
}
qtConfig(charts-scatter-chart) {
    SUBDIRS += \
        scatterchart \
        scatterinteractions
}
qtHaveModule(quick) {
    SUBDIRS += \
           qmlaxes \
           qmlchart \
           qmlcustomizations \
           qmlcustomlegend \
           qmlf1legends \
           qmloscilloscope \
           qmlpolarchart \
           qmlweather
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


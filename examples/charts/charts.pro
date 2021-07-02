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
        splinechart \
        pointsselectionandmarkers
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
        temperaturerecords \
        selectedbar
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
           qmlchart \
           qmlcustomizations \
           qmlcustomlegend \
           qmlf1legends \
           qmloscilloscope \
           qmlweather
}

qtHaveModule(multimedia) {
    # SUBDIRS += audio // QTBUG-94181
} else {
    message("QtMultimedia library not available. Some examples are disabled.")
}

qtConfig(opengl) {
    SUBDIRS += openglseries
} else {
    message("OpenGL not available. Some examples are disabled.")
}

qtConfig(charts-datetime-axis) {
    SUBDIRS += datetimeaxis
    qtHaveModule(quick): SUBDIRS += qmlaxes qmlpolarchart
}


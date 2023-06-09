include($$OUT_PWD/../../src/charts/qtcharts-config.pri)
QT_FOR_CONFIG += charts
TEMPLATE = subdirs

qtConfig(charts-line-chart) {
    SUBDIRS += zoomlinechart
}
qtHaveModule(quick):qtConfig(charts-line-chart) {
    qtConfig(charts-scatter-chart): SUBDIRS += qmloscilloscope
    qtConfig(charts-bar-chart): SUBDIRS += qmlweather
}

qtHaveModule(multimedia) {
    qtConfig(charts-line-chart): SUBDIRS += audio
} else {
    message("QtMultimedia library not available. Some examples are disabled.")
}

qtConfig(opengl) {
    qtConfig(charts-line-chart): SUBDIRS += openglseries
} else {
    message("OpenGL not available. Some examples are disabled.")
}

qtConfig(charts-line-chart):qtConfig(charts-spline-chart):qtConfig(charts-bar-chart):
    qtConfig(charts-pie-chart):qtConfig(charts-boxplot-chart):qtConfig(charts-candlestick-chart):
    qtConfig(charts-scatter-chart):qtConfig(charts-datetime-axis) {
    SUBDIRS += chartsgallery
    qtHaveModule(quick): SUBDIRS += qmlchartsgallery
}


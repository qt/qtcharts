qt_path_join(destination ${QT_INSTALL_DIR} "${INSTALL_QMLDIR}/QtCharts/designer/default")
qt_copy_or_install(
    FILES
        AreaSeries.qml
        BarSeries.qml
        BoxPlotSeries.qml
        HorizontalBarSeries.qml
        HorizontalPercentBarSeries.qml
        HorizontalStackedBarSeries.qml
        LineSeries.qml
        PercentBarSeries.qml
        PieSeries.qml
        ScatterSeries.qml
        SplineSeries.qml
        StackedBarSeries.qml
        PolarAreaSeries.qml
        PolarLineSeries.qml
        PolarScatterSeries.qml
        PolarSplineSeries.qml
    DESTINATION "${destination}"
)

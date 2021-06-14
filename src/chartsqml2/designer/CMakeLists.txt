qt_copy_or_install(
    FILES
        ChartViewSpecifics.qml
        qtcharts.metainfo
    DESTINATION "${INSTALL_QMLDIR}/QtCharts/designer"
)

add_subdirectory(default)
add_subdirectory(images)

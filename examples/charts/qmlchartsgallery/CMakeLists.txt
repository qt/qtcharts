# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qmlchartsgallery LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/qmlchartsgallery")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_standard_project_setup()

qt_add_executable(qmlchartsgallery
    main.cpp
)

set_target_properties(qmlchartsgallery PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlchartsgallery PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/AreaSeries.qml"
    "qml/BarSeries.qml"
    "qml/BarSeriesHorizontal.qml"
    "qml/BarSeriesPercent.qml"
    "qml/BarSeriesPercentHorizontal.qml"
    "qml/BarSeriesStacked.qml"
    "qml/BarSeriesStackedHorizontal.qml"
    "qml/BoxPlotSeries.qml"
    "qml/CandlestickSeries.qml"
    "qml/CategoryAxis.qml"
    "qml/CategoryAxisPolar.qml"
    "qml/DateTimeAxis.qml"
    "qml/DateTimeAxisPolar.qml"
    "qml/Donut.qml"
    "qml/LineSeries.qml"
    "qml/Main.qml"
    "qml/PieChart.qml"
    "qml/SplineSeries.qml"
    "qml/ScatterSeries.qml"
    "qml/TwoSeries.qml"
    "qml/TwoSeriesPolar.qml"
    "qml/WheelOfFortune.qml"
    "qml/customlegend/AnimatedAreaSeries.qml"
    "qml/customlegend/ChartViewHighlighted.qml"
    "qml/customlegend/ChartViewSelector.qml"
    "qml/customlegend/ChartViewStacked.qml"
    "qml/customlegend/CustomLegend.qml"
    "qml/customlegend/Main.qml"
    "qml/f1legends/F1Legends.qml"
    "qml/f1legends/SpeedsList.qml"
)

qt6_add_resources(qmlchartsgallery "qmlchartsgallery"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS qmlchartsgallery
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

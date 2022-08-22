# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qmlchartproperties.pro.

#####################################################################
## qmlchartproperties Binary:
#####################################################################

qt_internal_add_manual_test(qmlchartproperties
    GUI
    SOURCES
        main.cpp
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/qmlchartproperties/AreaChart.qml"
    "qml/qmlchartproperties/AreaEditor.qml"
    "qml/qmlchartproperties/BarChart.qml"
    "qml/qmlchartproperties/BarEditor.qml"
    "qml/qmlchartproperties/Button.qml"
    "qml/qmlchartproperties/Chart.qml"
    "qml/qmlchartproperties/ChartEditor.qml"
    "qml/qmlchartproperties/ChartEditorAxis.qml"
    "qml/qmlchartproperties/ChartEditorLegend.qml"
    "qml/qmlchartproperties/ChartEditorProperties.qml"
    "qml/qmlchartproperties/ChartEditorSeries.qml"
    "qml/qmlchartproperties/ChartEditorTitle.qml"
    "qml/qmlchartproperties/FontEditor.qml"
    "qml/qmlchartproperties/HorizontalBarChart.qml"
    "qml/qmlchartproperties/HorizontalPercentBarChart.qml"
    "qml/qmlchartproperties/HorizontalStackedBarChart.qml"
    "qml/qmlchartproperties/LineChart.qml"
    "qml/qmlchartproperties/LineEditor.qml"
    "qml/qmlchartproperties/PercentBarChart.qml"
    "qml/qmlchartproperties/PieChart.qml"
    "qml/qmlchartproperties/PieEditor.qml"
    "qml/qmlchartproperties/ScatterChart.qml"
    "qml/qmlchartproperties/ScatterEditor.qml"
    "qml/qmlchartproperties/SplineChart.qml"
    "qml/qmlchartproperties/StackedBarChart.qml"
    "qml/qmlchartproperties/main.qml"
)

qt_internal_add_resource(qmlchartproperties "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)


#### Keys ignored in scope 1:.:.:qmlchartproperties.pro:<TRUE>:
# OTHER_FILES = "qml/qmlchartproperties/*"

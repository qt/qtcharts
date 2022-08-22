# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qmlchartaxis.pro.

#####################################################################
## qmlchartaxis Binary:
#####################################################################

qt_internal_add_manual_test(qmlchartaxis
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
    "qml/qmlchartaxis/Button.qml"
    "qml/qmlchartaxis/ChartAxes.qml"
    "qml/qmlchartaxis/ChartAxesRevert.qml"
    "qml/qmlchartaxis/ConfiguringDynamically.qml"
    "qml/qmlchartaxis/CreatingDynamically.qml"
    "qml/qmlchartaxis/DefaultAndUserDefined.qml"
    "qml/qmlchartaxis/DefaultAxes.qml"
    "qml/qmlchartaxis/DefaultAxesRevert.qml"
    "qml/qmlchartaxis/SeriesSpecificDynamic.qml"
    "qml/qmlchartaxis/SwitchingDynamically.qml"
    "qml/qmlchartaxis/UserDefined.qml"
    "qml/qmlchartaxis/UserDefinedRevert.qml"
    "qml/qmlchartaxis/main.qml"
)

qt_internal_add_resource(qmlchartaxis "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)


#### Keys ignored in scope 1:.:.:qmlchartaxis.pro:<TRUE>:
# OTHER_FILES = "qml/qmlchartaxis/*"

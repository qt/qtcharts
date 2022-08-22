# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qmlcustomlegend LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/qmlcustomlegend")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_add_executable(qmlcustomlegend
    main.cpp
)

set_target_properties(qmlcustomlegend PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlcustomlegend PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/qmlcustomlegend/AnimatedAreaSeries.qml"
    "qml/qmlcustomlegend/ChartViewHighlighted.qml"
    "qml/qmlcustomlegend/ChartViewSelector.qml"
    "qml/qmlcustomlegend/ChartViewStacked.qml"
    "qml/qmlcustomlegend/CustomLegend.qml"
    "qml/qmlcustomlegend/main.qml"
)

qt6_add_resources(qmlcustomlegend "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS qmlcustomlegend
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

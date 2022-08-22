# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qmlchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/qmlchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_add_executable(qmlchart
    main.cpp
)

set_target_properties(qmlchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/qmlchart/MainForm.ui.qml"
    "qml/qmlchart/View1.qml"
    "qml/qmlchart/View10.qml"
    "qml/qmlchart/View11.qml"
    "qml/qmlchart/View12.qml"
    "qml/qmlchart/View2.qml"
    "qml/qmlchart/View3.qml"
    "qml/qmlchart/View4.qml"
    "qml/qmlchart/View5.qml"
    "qml/qmlchart/View6.qml"
    "qml/qmlchart/View7.qml"
    "qml/qmlchart/View8.qml"
    "qml/qmlchart/View9.qml"
    "qml/qmlchart/main.qml"
)

qt6_add_resources(qmlchart "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS qmlchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

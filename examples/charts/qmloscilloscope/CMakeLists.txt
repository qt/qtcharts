# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qmloscilloscope LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/qmloscilloscope")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_standard_project_setup()

qt_add_executable(qmloscilloscope
    datasource.cpp datasource.h
    main.cpp
)

set_target_properties(qmloscilloscope PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmloscilloscope PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/qmloscilloscope/ControlPanel.qml"
    "qml/qmloscilloscope/MultiButton.qml"
    "qml/qmloscilloscope/ScopeView.qml"
    "qml/qmloscilloscope/main.qml"
)

qt6_add_resources(qmloscilloscope "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS qmloscilloscope
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

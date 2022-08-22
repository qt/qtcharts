# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qmlf1legends LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/qmlf1legends")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_add_executable(qmlf1legends
    main.cpp
)

set_target_properties(qmlf1legends PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlf1legends PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/qmlf1legends/SpeedsList.qml"
    "qml/qmlf1legends/main.qml"
)

qt6_add_resources(qmlf1legends "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS qmlf1legends
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

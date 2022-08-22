# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qmlpiechart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/qmlpiechart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_add_executable(qmlpiechart
    main.cpp
)

set_target_properties(qmlpiechart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlpiechart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(resources_resource_files
    "qml/qmlpiechart/main.qml"
)

qt6_add_resources(qmlpiechart "resources"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS qmlpiechart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

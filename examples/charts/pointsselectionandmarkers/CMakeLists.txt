# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.14)
project(pointsselectionandmarkers LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/pointsselectionandmarkers")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(pointsselectionandmarkers
    utilities.h utilities.cpp
    main.cpp
)

set_target_properties(pointsselectionandmarkers PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(pointsselectionandmarkers PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

set(pointsselectionandmarkers_resource_files
    "blue_triangle.png"
    "green_triangle.png"
)

qt6_add_resources(pointsselectionandmarkers "images"
    PREFIX
        "/"
    FILES
        ${pointsselectionandmarkers_resource_files}
)

install(TARGETS pointsselectionandmarkers
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

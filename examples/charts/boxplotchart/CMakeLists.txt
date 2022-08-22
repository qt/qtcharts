# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(boxplotchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/boxplotchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(boxplotchart
    boxdatareader.cpp boxdatareader.h
    main.cpp
)

set_target_properties(boxplotchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(boxplotchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

# Resources:
set_source_files_properties("acme_data.txt"
    PROPERTIES QT_RESOURCE_ALIAS "acme"
)

set_source_files_properties("boxwhisk_data.txt"
    PROPERTIES QT_RESOURCE_ALIAS "boxwhisk"
)

set(boxplotdata_resource_files
    "acme_data.txt"
    "boxwhisk_data.txt"
)

qt6_add_resources(boxplotchart "boxplotdata"
    PREFIX
        "/"
    FILES
        ${boxplotdata_resource_files}
)

install(TARGETS boxplotchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

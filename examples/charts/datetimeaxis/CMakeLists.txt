# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(datetimeaxis LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/datetimeaxis")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(datetimeaxis
    main.cpp
)

set_target_properties(datetimeaxis PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(datetimeaxis PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

# Resources:
set_source_files_properties("sun_spots.txt"
    PROPERTIES QT_RESOURCE_ALIAS "sun"
)

set(sundata_resource_files
    "sun_spots.txt"
)

qt6_add_resources(datetimeaxis "sundata"
    PREFIX
        "/"
    FILES
        ${sundata_resource_files}
)

install(TARGETS datetimeaxis
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

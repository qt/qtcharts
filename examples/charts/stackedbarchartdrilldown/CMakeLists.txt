# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(stackedbarchartdrilldown LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/stackedbarchartdrilldown")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(stackedbarchartdrilldown
    drilldownchart.cpp drilldownchart.h
    drilldownseries.cpp drilldownseries.h
    main.cpp
)

set_target_properties(stackedbarchartdrilldown PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(stackedbarchartdrilldown PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS stackedbarchartdrilldown
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

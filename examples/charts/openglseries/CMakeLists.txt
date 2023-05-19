# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(openglseries LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/openglseries")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_standard_project_setup()

qt_add_executable(openglseries
    datasource.cpp datasource.h
    main.cpp
)

set_target_properties(openglseries PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(openglseries PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS openglseries
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(chartthemes LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/chartthemes")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(chartthemes
    main.cpp
    themewidget.cpp themewidget.h themewidget.ui
)

set_target_properties(chartthemes PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chartthemes PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS chartthemes
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

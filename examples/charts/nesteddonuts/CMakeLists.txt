# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(nesteddonuts LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/nesteddonuts")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(nesteddonuts
    main.cpp
    widget.cpp widget.h
)

set_target_properties(nesteddonuts PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(nesteddonuts PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS nesteddonuts
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

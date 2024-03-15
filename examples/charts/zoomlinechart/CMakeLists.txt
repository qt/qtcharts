# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(zoomlinechart LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/zoomlinechart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_standard_project_setup()

qt_add_executable(zoomlinechart
    chart.cpp chart.h
    chartview.cpp chartview.h
    main.cpp
)

set_target_properties(zoomlinechart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(zoomlinechart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS zoomlinechart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

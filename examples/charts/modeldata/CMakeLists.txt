# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(modeldata LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/modeldata")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(modeldata
    customtablemodel.cpp customtablemodel.h
    main.cpp
    tablewidget.cpp tablewidget.h
)

set_target_properties(modeldata PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(modeldata PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS modeldata
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(wavechart LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

# Generated from wavechart.pro.

#####################################################################
## wavechart Binary:
#####################################################################

qt_internal_add_manual_test(wavechart
    GUI
    SOURCES
        main.cpp
        wavechart.cpp wavechart.h
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
)

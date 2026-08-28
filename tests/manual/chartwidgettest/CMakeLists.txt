# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(chartwidgettest LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

# Generated from chartwidgettest.pro.

#####################################################################
## chartwidgettest Binary:
#####################################################################

qt_internal_add_manual_test(chartwidgettest
    GUI
    SOURCES
        dataseriedialog.cpp dataseriedialog.h
        main.cpp
        mainwidget.cpp mainwidget.h
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:chartwidgettest.pro:<TRUE>:
# TEMPLATE = "app"

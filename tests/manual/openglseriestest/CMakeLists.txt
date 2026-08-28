# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(openglseriestest LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

# Generated from openglseriestest.pro.

#####################################################################
## openglseriestest Binary:
#####################################################################

qt_internal_add_manual_test(openglseriestest
    GUI
    SOURCES
        chartview.cpp chartview.h
        datasource.cpp datasource.h
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
    NO_PCH_SOURCES
        mainwindow.cpp # undef QT_NO_FOREACH
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

#### Keys ignored in scope 1:.:.:openglseriestest.pro:<TRUE>:
# TEMPLATE = "app"

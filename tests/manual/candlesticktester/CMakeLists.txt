# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(candlesticktester LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

# Generated from candlesticktester.pro.

#####################################################################
## candlesticktester Binary:
#####################################################################

qt_internal_add_manual_test(candlesticktester
    GUI
    SOURCES
        customtablemodel.cpp customtablemodel.h
        main.cpp
        mainwidget.cpp mainwidget.h
    NO_PCH_SOURCES
        customtablemodel.cpp # undef QT_NO_FOREACH
        mainwidget.cpp # undef QT_NO_FOREACH
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

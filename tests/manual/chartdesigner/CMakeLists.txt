# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(chartdesigner LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

# Generated from chartdesigner.pro.

#####################################################################
## chartdesigner Binary:
#####################################################################

qt_internal_add_manual_test(chartdesigner
    GUI
    SOURCES
        brushwidget.cpp brushwidget.h
        engine.cpp engine.h
        main.cpp
        mainwindow.cpp mainwindow.h
        objectinspectorwidget.cpp objectinspectorwidget.h
        penwidget.cpp penwidget.h
    NO_PCH_SOURCES
        engine.cpp # undef QT_NO_FOREACH
        mainwindow.cpp # undef QT_NO_FOREACH
    LIBRARIES
        Qt::Charts
        Qt::Gui
)

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:chartdesigner.pro:NOT system_build AND APPLE:
# QMAKE_POST_LINK = "$$MAC_POST_LINK_PREFIX $$MAC_TESTS_BIN_DIR"

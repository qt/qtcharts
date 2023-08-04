# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qtcharts.pro.

cmake_minimum_required(VERSION 3.16)

include(.cmake.conf)
project(QtCharts
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt Charts Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

# Make sure we use the fixed BASE argument of qt_add_resource.
set(QT_USE_FIXED_QT_ADD_RESOURCE_BASE TRUE)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core) # special case
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS Gui Widgets OpenGL OpenGLWidgets Multimedia Quick Qml QuickTest Test) # special case
qt_internal_project_setup()

#special case begin
macro(assertTargets)
    foreach(qtTarget IN ITEMS ${ARGN})
        if(NOT TARGET Qt::${qtTarget})
           message(NOTICE "Skipping the build as the condition \"TARGET Qt::${qtTarget}\" is not met.")
           return()
        endif()
    endforeach()
endmacro()

assertTargets(Gui Widgets)
#special case end

if(NOT QT_FEATURE_graphicsview) # special case
    message(NOTICE "Skipping the build as the feature 'graphics view' is not met.") # special case
    return() # special case
endif() # special case

qt_build_repo()

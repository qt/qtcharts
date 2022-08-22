# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from designer.pro.

#####################################################################
## qtchartsdesigner Generic Library:
#####################################################################

qt_internal_add_cmake_library(qtchartsdesigner
    MODULE
    INSTALL_DIRECTORY "$$[QT_INSTALL_PLUGINS]/designer"
    SOURCES
        qchartsplugin.cpp qchartsplugin.h
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../../../include
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Core
        Qt::Designer
        Qt::Gui
)

# Resources:
set(qchartsplugin_resource_files
    "qcharts.png"
)

qt_internal_add_resource(qtchartsdesigner "qchartsplugin"
    PREFIX
        "/images"
    FILES
        ${qchartsplugin_resource_files}
)


#### Keys ignored in scope 1:.:.:designer.pro:<TRUE>:
# DEPENDPATH = "$$PWD"
# INSTALLS = "target"
# TEMPLATE = "lib"
# target.path = "$$[QT_INSTALL_PLUGINS]/designer"

qt_autogen_tools_initial_setup(qtchartsdesigner)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

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

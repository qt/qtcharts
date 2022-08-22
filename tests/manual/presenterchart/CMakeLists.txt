# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from presenterchart.pro.

#####################################################################
## presenterchart Binary:
#####################################################################

qt_internal_add_manual_test(presenterchart
    GUI
    SOURCES
        chartview.cpp chartview.h
        main.cpp
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

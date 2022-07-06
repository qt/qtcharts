# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from presenterchart.pro.

#####################################################################
## presenterchart Binary:
#####################################################################

qt_internal_add_manual_test(presenterchart
    GUI
    SOURCES
        chartview.cpp chartview.h
        main.cpp
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

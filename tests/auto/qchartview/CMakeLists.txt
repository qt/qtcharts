# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qchartview.pro.

#####################################################################
## qchartview Test:
#####################################################################

qt_internal_add_test(tst_qchartview
    SOURCES
        ../inc/tst_definitions.h
        tst_qchartview.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

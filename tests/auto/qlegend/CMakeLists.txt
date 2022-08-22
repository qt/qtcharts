# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qlegend.pro.

#####################################################################
## qlegend Test:
#####################################################################

qt_internal_add_test(tst_qlegend
    SOURCES
        ../inc/tst_definitions.h
        tst_qlegend.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qpieslice.pro.

#####################################################################
## qpieslice Test:
#####################################################################

qt_internal_add_test(tst_qpieslice
    SOURCES
        ../inc/tst_definitions.h
        tst_qpieslice.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qpieseries.pro.

#####################################################################
## qpieseries Test:
#####################################################################

qt_internal_add_test(tst_qpieseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qpieseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

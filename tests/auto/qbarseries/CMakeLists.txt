# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qbarseries.pro.

#####################################################################
## qbarseries Test:
#####################################################################

qt_internal_add_test(tst_qbarseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qbarseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

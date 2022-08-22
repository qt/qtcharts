# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qbarset.pro.

#####################################################################
## qbarset Test:
#####################################################################

qt_internal_add_test(tst_qbarset
    SOURCES
        ../inc/tst_definitions.h
        tst_qbarset.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

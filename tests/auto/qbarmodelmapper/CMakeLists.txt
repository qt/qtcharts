# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qbarmodelmapper.pro.

#####################################################################
## qbarmodelmapper Test:
#####################################################################

qt_internal_add_test(tst_qbarmodelmapper
    SOURCES
        ../inc/tst_definitions.h
        tst_qbarmodelmapper.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
        Qt::Charts # special case
        Qt::Test # special case
)

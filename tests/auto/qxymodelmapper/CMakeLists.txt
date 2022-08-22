# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qxymodelmapper.pro.

#####################################################################
## qxymodelmapper Test:
#####################################################################

qt_internal_add_test(tst_qxymodelmapper
    SOURCES
        ../inc/tst_definitions.h
        tst_qxymodelmapper.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

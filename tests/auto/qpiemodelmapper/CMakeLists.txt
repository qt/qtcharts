# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qpiemodelmapper.pro.

#####################################################################
## qpiemodelmapper Test:
#####################################################################

qt_internal_add_test(tst_qpiemodelmapper
    SOURCES
        ../inc/tst_definitions.h
        tst_qpiemodelmapper.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

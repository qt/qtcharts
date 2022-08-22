# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qcandlestickmodelmapper.pro.

#####################################################################
## qcandlestickmodelmapper Test:
#####################################################################

qt_internal_add_test(tst_qcandlestickmodelmapper
    SOURCES
        ../inc/tst_definitions.h
        tst_qcandlestickmodelmapper.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qcandlestickset.pro.

#####################################################################
## qcandlestickset Test:
#####################################################################

qt_internal_add_test(tst_qcandlestickset
    SOURCES
        ../inc/tst_definitions.h
        tst_qcandlestickset.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

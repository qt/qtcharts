# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qcandlestickseries.pro.

#####################################################################
## qcandlestickseries Test:
#####################################################################

qt_internal_add_test(tst_qcandlestickseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qcandlestickseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

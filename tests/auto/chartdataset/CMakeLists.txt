# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from chartdataset.pro.

#####################################################################
## chartdataset Test:
#####################################################################

qt_internal_add_test(tst_chartdataset
    SOURCES
        ../inc/tst_definitions.h
        tst_chartdataset.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::ChartsPrivate
        Qt::CorePrivate
        Qt::Gui
        Qt::Widgets
)

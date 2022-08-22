# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qsplineseries.pro.

#####################################################################
## qsplineseries Test:
#####################################################################

qt_internal_add_test(tst_qsplineseries
    SOURCES
        ../inc/tst_definitions.h
        ../qxyseries/tst_qxyseries.cpp ../qxyseries/tst_qxyseries.h
        tst_qsplineseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

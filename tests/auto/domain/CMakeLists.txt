# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from domain.pro.

#####################################################################
## domain Test:
#####################################################################

qt_internal_add_test(tst_domain
    SOURCES
        ../inc/tst_definitions.h
        tst_domain.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::ChartsPrivate
        Qt::CorePrivate
        Qt::Gui
        Qt::Widgets
)

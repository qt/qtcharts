# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qpieseries.pro.

#####################################################################
## qpieseries Test:
#####################################################################

qt_internal_add_test(qpieseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qpieseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

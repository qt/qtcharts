# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qchart.pro.

#####################################################################
## qchart Test:
#####################################################################

qt_internal_add_test(tst_qchart
    SOURCES
        ../inc/tst_definitions.h
        tst_qchart.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

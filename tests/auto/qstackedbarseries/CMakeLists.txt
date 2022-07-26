# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qstackedbarseries.pro.

#####################################################################
## qstackedbarseries Test:
#####################################################################

qt_internal_add_test(tst_qstackedbarseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qstackedbarseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

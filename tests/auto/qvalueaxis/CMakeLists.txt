# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qvalueaxis.pro.

#####################################################################
## qvalueaxis Test:
#####################################################################

qt_internal_add_test(tst_qvalueaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qvalueaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

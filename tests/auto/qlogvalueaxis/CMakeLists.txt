# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qlogvalueaxis.pro.

#####################################################################
## qlogvalueaxis Test:
#####################################################################

qt_internal_add_test(tst_qlogvalueaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qlogvalueaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

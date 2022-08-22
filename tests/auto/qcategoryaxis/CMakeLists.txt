# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qcategoryaxis.pro.

#####################################################################
## qcategoryaxis Test:
#####################################################################

qt_internal_add_test(tst_qcategoryaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qcategoryaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from polarcharttest.pro.

#####################################################################
## polarcharttest Binary:
#####################################################################

qt_internal_add_manual_test(polarcharttest
    GUI
    SOURCES
        chartview.cpp chartview.h
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
    INCLUDE_DIRECTORIES
        .
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

#### Keys ignored in scope 1:.:.:polarcharttest.pro:<TRUE>:
# TEMPLATE = "app"

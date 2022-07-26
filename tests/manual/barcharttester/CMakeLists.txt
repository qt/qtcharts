# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from barcharttester.pro.

#####################################################################
## barcharttester Binary:
#####################################################################

qt_internal_add_manual_test(barcharttester
    GUI
    SOURCES
        chart-widget.cpp chart-widget.h
        main.cpp
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:barcharttester.pro:<TRUE>:
# TEMPLATE = "app"

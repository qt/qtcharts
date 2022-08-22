# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

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

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from candlesticktester.pro.

#####################################################################
## candlesticktester Binary:
#####################################################################

qt_internal_add_manual_test(candlesticktester
    GUI
    SOURCES
        customtablemodel.cpp customtablemodel.h
        main.cpp
        mainwidget.cpp mainwidget.h
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

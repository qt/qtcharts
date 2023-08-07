# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

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
    NO_PCH_SOURCES
        customtablemodel.cpp # undef QT_NO_FOREACH
        mainwidget.cpp # undef QT_NO_FOREACH
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

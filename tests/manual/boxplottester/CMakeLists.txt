# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from boxplottester.pro.

#####################################################################
## boxplottester Binary:
#####################################################################

qt_internal_add_manual_test(boxplottester
    GUI
    SOURCES
        customtablemodel.cpp customtablemodel.h
        main.cpp
        mainwidget.cpp mainwidget.h
        pentool.cpp pentool.h
    NO_PCH_SOURCES
        customtablemodel.cpp # undef QT_NO_FOREACH
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:boxplottester.pro:<TRUE>:
# TEMPLATE = "app"

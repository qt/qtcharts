# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from openglseriestest.pro.

#####################################################################
## openglseriestest Binary:
#####################################################################

qt_internal_add_manual_test(openglseriestest
    GUI
    SOURCES
        chartview.cpp chartview.h
        datasource.cpp datasource.h
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

#### Keys ignored in scope 1:.:.:openglseriestest.pro:<TRUE>:
# TEMPLATE = "app"

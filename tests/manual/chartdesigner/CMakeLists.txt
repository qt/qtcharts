# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from chartdesigner.pro.

#####################################################################
## chartdesigner Binary:
#####################################################################

qt_internal_add_manual_test(chartdesigner
    GUI
    SOURCES
        brushwidget.cpp brushwidget.h
        engine.cpp engine.h
        main.cpp
        mainwindow.cpp mainwindow.h
        objectinspectorwidget.cpp objectinspectorwidget.h
        penwidget.cpp penwidget.h
    LIBRARIES
        Qt::Charts
        Qt::Gui
)

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:chartdesigner.pro:NOT system_build AND APPLE:
# QMAKE_POST_LINK = "$$MAC_POST_LINK_PREFIX $$MAC_TESTS_BIN_DIR"

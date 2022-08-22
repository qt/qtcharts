# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from demoLauncher.pro.

#####################################################################
## demoLauncher Binary:
#####################################################################

qt_internal_add_executable(demoLauncher
    GUI
    SOURCES
        graphicsbutton.cpp graphicsbutton.h
        main.cpp
        widget.cpp widget.h
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Widgets
)

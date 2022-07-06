# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from manual.pro.

add_subdirectory(presenterchart)
add_subdirectory(polarcharttest)
add_subdirectory(boxplottester)
add_subdirectory(candlesticktester)
add_subdirectory(barcharttester)
if(QT_FEATURE_opengl)
    add_subdirectory(chartwidgettest)
    add_subdirectory(wavechart)
    add_subdirectory(chartviewer)
    add_subdirectory(openglseriestest)
endif()
if(TARGET Qt::Quick)
    add_subdirectory(qmlchartproperties)
    add_subdirectory(qmlchartaxis)
endif()

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from chartviewer.pro.

#####################################################################
## chartviewer Binary:
#####################################################################

qt_internal_add_manual_test(chartviewer
    GUI
    SOURCES
        charts.h
        charts/axis/barcategoryaxisx.cpp
        charts/axis/barcategoryaxisxlogy.cpp
        charts/axis/barcategoryaxisy.cpp
        charts/axis/barcategoryaxisylogx.cpp
        charts/axis/categoryaxis.cpp
        charts/axis/logvalueaxisx.cpp
        charts/axis/logvalueaxisy.cpp
        charts/axis/valueaxis.cpp
        charts/barseries/horizontalbarchart.cpp
        charts/barseries/horizontalpercentbarchart.cpp
        charts/barseries/horizontalstackedbarchart.cpp
        charts/barseries/verticalbarchart.cpp
        charts/barseries/verticalpercentbarchart.cpp
        charts/barseries/verticalstackedbarchart.cpp
        charts/domain/barlogx.cpp
        charts/domain/barlogy.cpp
        charts/domain/barpercentlogx.cpp
        charts/domain/barpercentlogy.cpp
        charts/domain/barstackedlogx.cpp
        charts/domain/barstackedlogy.cpp
        charts/domain/linelogxlogy.cpp
        charts/domain/linelogxy.cpp
        charts/domain/linexlogy.cpp
        charts/domain/scatterlogxlogy.cpp
        charts/domain/scatterlogxy.cpp
        charts/domain/scatterxlogy.cpp
        charts/domain/splinelogxlogy.cpp
        charts/domain/splinelogxy.cpp
        charts/domain/splinexlogy.cpp
        charts/font/font.cpp
        charts/multiaxis/multivalueaxis.cpp
        charts/multiaxis/multivalueaxis2.cpp
        charts/multiaxis/multivalueaxis3.cpp
        charts/multiaxis/multivalueaxis4.cpp
        charts/multiaxis/multivaluebaraxis.cpp
        charts/pieseries/donutchart.cpp
        charts/pieseries/piechart.cpp
        charts/size/sizecharts.cpp
        charts/xyseries/areachart.cpp
        charts/xyseries/linechart.cpp
        charts/xyseries/scatterchart.cpp
        charts/xyseries/splinechart.cpp
        grid.cpp grid.h
        main.cpp
        model.h
        view.cpp view.h
        window.cpp window.h
    NO_PCH_SOURCES
        # these all contain Q_FOREACH, so need to undef QT_NO_FOREACH
        charts/axis/barcategoryaxisx.cpp
        charts/axis/barcategoryaxisxlogy.cpp
        charts/axis/barcategoryaxisy.cpp
        charts/axis/barcategoryaxisylogx.cpp
        charts/axis/categoryaxis.cpp
        charts/axis/logvalueaxisx.cpp
        charts/axis/logvalueaxisy.cpp
        charts/axis/valueaxis.cpp
        charts/barseries/horizontalbarchart.cpp
        charts/barseries/horizontalpercentbarchart.cpp
        charts/barseries/horizontalstackedbarchart.cpp
        charts/barseries/verticalbarchart.cpp
        charts/barseries/verticalpercentbarchart.cpp
        charts/barseries/verticalstackedbarchart.cpp
        charts/domain/barlogx.cpp
        charts/domain/barlogy.cpp
        charts/domain/barpercentlogx.cpp
        charts/domain/barpercentlogy.cpp
        charts/domain/barstackedlogx.cpp
        charts/domain/barstackedlogy.cpp
        charts/domain/linelogxlogy.cpp
        charts/domain/linelogxy.cpp
        charts/domain/linexlogy.cpp
        charts/domain/scatterlogxlogy.cpp
        charts/domain/scatterlogxy.cpp
        charts/domain/scatterxlogy.cpp
        charts/domain/splinelogxlogy.cpp
        charts/domain/splinelogxy.cpp
        charts/domain/splinexlogy.cpp
        charts/font/font.cpp
        charts/multiaxis/multivalueaxis.cpp
        charts/multiaxis/multivalueaxis2.cpp
        charts/multiaxis/multivalueaxis3.cpp
        charts/multiaxis/multivalueaxis4.cpp
        charts/multiaxis/multivaluebaraxis.cpp
        charts/pieseries/donutchart.cpp
        charts/pieseries/piechart.cpp
        charts/size/sizecharts.cpp
        charts/xyseries/linechart.cpp
        charts/xyseries/scatterchart.cpp
        charts/xyseries/splinechart.cpp
        grid.cpp
        window.cpp
        # end undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        .
        charts
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
)

## Scopes:
#####################################################################

qt_internal_extend_target(chartviewer CONDITION QT_FEATURE_charts_datetime_axis
    SOURCES
        charts/axis/datetimeaxisx.cpp
        charts/axis/datetimeaxisy.cpp
    NO_PCH_SOURCES
        charts/axis/datetimeaxisx.cpp # undef QT_NO_FOREACH
        charts/axis/datetimeaxisy.cpp # undef QT_NO_FOREACH
)

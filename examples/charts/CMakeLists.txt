# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(QT_FEATURE_charts_area_chart
        AND QT_FEATURE_charts_line_chart
        AND QT_FEATURE_charts_spline_chart
        AND QT_FEATURE_charts_bar_chart
        AND QT_FEATURE_charts_pie_chart
        AND QT_FEATURE_charts_boxplot_chart
        AND QT_FEATURE_charts_candlestick_chart
        AND QT_FEATURE_charts_scatter_chart
        AND QT_FEATURE_charts_datetime_axis)
    qt_internal_add_example(chartsgallery)
endif()

if(QT_FEATURE_charts_area_chart
        AND QT_FEATURE_charts_line_chart
        AND QT_FEATURE_charts_spline_chart
        AND QT_FEATURE_charts_bar_chart
        AND QT_FEATURE_charts_pie_chart
        AND QT_FEATURE_charts_boxplot_chart
        AND QT_FEATURE_charts_candlestick_chart
        AND QT_FEATURE_charts_scatter_chart
        AND QT_FEATURE_charts_datetime_axis
        AND TARGET Qt::Quick)
    qt_internal_add_example(qmlchartsgallery)
endif()

if(QT_FEATURE_charts_line_chart AND TARGET Qt::Multimedia)
    qt_internal_add_example(audio)
endif()

if(QT_FEATURE_opengl)
    qt_internal_add_example(openglseries)
endif()

if(QT_FEATURE_charts_line_chart)
    qt_internal_add_example(zoomlinechart)
endif()

if(QT_FEATURE_charts_line_chart AND QT_FEATURE_charts_scatter_chart AND TARGET Qt::Quick)
    qt_internal_add_example(qmloscilloscope)
endif()

if(QT_FEATURE_charts_line_chart AND QT_FEATURE_charts_bar_chart AND TARGET Qt::Quick)
    qt_internal_add_example(qmlweather)
endif()


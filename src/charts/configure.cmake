# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#### Inputs



#### Libraries



#### Tests



#### Features

qt_feature("charts-line-chart" PUBLIC
    LABEL "Line Chart"
    PURPOSE "Support for line charts"
)
qt_feature("charts-spline-chart" PUBLIC
    LABEL "Spline Chart"
    PURPOSE "Support for spline charts"
    CONDITION QT_FEATURE_charts_line_chart
)
qt_feature("charts-area-chart" PUBLIC
    LABEL "Area Chart"
    PURPOSE "Support for area charts"
    CONDITION QT_FEATURE_charts_line_chart
)
qt_feature("charts-scatter-chart" PUBLIC
    LABEL "Scatter Chart"
    PURPOSE "Support for scatter charts"
    CONDITION QT_FEATURE_charts_line_chart
)
qt_feature("charts-bar-chart" PUBLIC
    LABEL "Bar Chart"
    PURPOSE "Support for bar charts"
)
qt_feature("charts-pie-chart" PUBLIC
    LABEL "Pie Chart"
    PURPOSE "Support for pie charts"
)
qt_feature("charts-boxplot-chart" PUBLIC
    LABEL "Boxplot Chart"
    PURPOSE "Support for box plot charts"
)
qt_feature("charts-candlestick-chart" PUBLIC
    LABEL "Candlestick Chart"
    PURPOSE "Support for candlestick charts"
)
# special case begin
if(TARGET Qt6::Core)
    get_property(_qt_coord_type TARGET Qt6::Core PROPERTY INTERFACE_QT_COORD_TYPE)
else()
    set(_qt_coord_type double)
endif()
# special case end
qt_feature("charts-datetime-axis" PUBLIC
    LABEL "DateTime Axis"
    PURPOSE "Support for datetime axis"
    CONDITION _qt_coord_type STREQUAL "double" # special case
)
qt_configure_add_summary_section(NAME "Qt Charts Types")
qt_configure_add_summary_entry(ARGS "charts-area-chart")
qt_configure_add_summary_entry(ARGS "charts-line-chart")
qt_configure_add_summary_entry(ARGS "charts-spline-chart")
qt_configure_add_summary_entry(ARGS "charts-scatter-chart")
qt_configure_add_summary_entry(ARGS "charts-bar-chart")
qt_configure_add_summary_entry(ARGS "charts-pie-chart")
qt_configure_add_summary_entry(ARGS "charts-boxplot-chart")
qt_configure_add_summary_entry(ARGS "charts-candlestick-chart")
qt_configure_end_summary_section() # end of "Qt Charts Types" section
qt_configure_add_summary_section(NAME "Qt Axis Types")
qt_configure_add_summary_entry(ARGS "charts-datetime-axis")
qt_configure_end_summary_section() # end of "Qt Axis Types" section

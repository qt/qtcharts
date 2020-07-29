

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
qt_feature("charts-datetime-axis" PUBLIC
    LABEL "DateTime Axis"
    PURPOSE "Support for datetime axis"
    CONDITION NOT tests.charts-realfloat OR FIXME
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

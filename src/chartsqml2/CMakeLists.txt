# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_qml_module(ChartsQml
    URI "QtCharts" # special case
    VERSION "${PROJECT_VERSION}"
    CLASS_NAME QtChartsQml2Plugin
    PLUGIN_TARGET qtchartsqml2
    PAST_MAJOR_VERSIONS 1 2
    DESIGNER_SUPPORTED
    DEPENDENCIES
        QtQuick
        QtCharts
    SOURCES
        declarativeabstractrendernode_p.h
        declarativeaxes.cpp declarativeaxes_p.h
        declarativecategoryaxis.cpp declarativecategoryaxis_p.h
        declarativechart.cpp declarativechart_p.h
        declarativechartglobal_p.h
        declarativechartnode.cpp declarativechartnode_p.h
        declarativeforeigntypes_p.h
        declarativemargins.cpp declarativemargins_p.h
        declarativepolarchart.cpp declarativepolarchart_p.h
        declarativexypoint.cpp declarativexypoint_p.h
        declarativexyseries.cpp declarativexyseries_p.h
    DEFINES
        QT_BUILD_QMLCHARTS_LIB
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
    LIBRARIES
        Qt::ChartsPrivate
        Qt::CorePrivate
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
    GENERATE_CPP_EXPORTS
    GENERATE_PRIVATE_CPP_EXPORTS
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_opengl
    SOURCES
        declarativeopenglrendernode.cpp declarativeopenglrendernode_p.h
    PUBLIC_LIBRARIES
        Qt::OpenGL
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_line_chart
    SOURCES
        declarativelineseries.cpp declarativelineseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_spline_chart
    SOURCES
        declarativesplineseries.cpp declarativesplineseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_area_chart
    SOURCES
        declarativeareaseries.cpp declarativeareaseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_scatter_chart
    SOURCES
        declarativescatterseries.cpp declarativescatterseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_pie_chart
    SOURCES
        declarativepieseries.cpp declarativepieseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_bar_chart
    SOURCES
        declarativebarseries.cpp declarativebarseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_boxplot_chart
    SOURCES
        declarativeboxplotseries.cpp declarativeboxplotseries_p.h
)

qt_internal_extend_target(ChartsQml CONDITION QT_FEATURE_charts_candlestick_chart
    SOURCES
        declarativecandlestickseries.cpp declarativecandlestickseries_p.h
)

# Warning: The files in the "designer" directory are _not_ part of this QML module.
#          That is the sole reason why we install them manually.
#          All files that do belong to the QML module _must_ be passed using the
#          QML_FILES option. You should _never_ install them manually.
add_subdirectory(designer)

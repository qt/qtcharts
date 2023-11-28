# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from charts.pro.

#####################################################################
## Charts Module:
#####################################################################

qt_internal_add_module(Charts
    TARGET_PRODUCT "Qt Charts (Qt ${PROJECT_VERSION})"
    TARGET_DESCRIPTION "Charts component for Qt."
    SOURCES
        animations/axisanimation.cpp animations/axisanimation_p.h
        animations/chartanimation.cpp animations/chartanimation_p.h
        animations/xyanimation.cpp animations/xyanimation_p.h
        axis/barcategoryaxis/chartbarcategoryaxisx.cpp axis/barcategoryaxis/chartbarcategoryaxisx_p.h
        axis/barcategoryaxis/chartbarcategoryaxisy.cpp axis/barcategoryaxis/chartbarcategoryaxisy_p.h
        axis/barcategoryaxis/qbarcategoryaxis.cpp axis/barcategoryaxis/qbarcategoryaxis.h axis/barcategoryaxis/qbarcategoryaxis_p.h
        axis/cartesianchartaxis.cpp axis/cartesianchartaxis_p.h
        axis/categoryaxis/chartcategoryaxisx.cpp axis/categoryaxis/chartcategoryaxisx_p.h
        axis/categoryaxis/chartcategoryaxisy.cpp axis/categoryaxis/chartcategoryaxisy_p.h
        axis/categoryaxis/polarchartcategoryaxisangular.cpp axis/categoryaxis/polarchartcategoryaxisangular_p.h
        axis/categoryaxis/polarchartcategoryaxisradial.cpp axis/categoryaxis/polarchartcategoryaxisradial_p.h
        axis/categoryaxis/qcategoryaxis.cpp axis/categoryaxis/qcategoryaxis.h axis/categoryaxis/qcategoryaxis_p.h
        axis/coloraxis/qcoloraxis.cpp axis/coloraxis/qcoloraxis.h axis/coloraxis/qcoloraxis_p.h
        axis/coloraxis/chartcoloraxisy.cpp axis/coloraxis/chartcoloraxisy_p.h
        axis/coloraxis/chartcoloraxisx.cpp axis/coloraxis/chartcoloraxisx_p.h
        axis/chartaxiselement.cpp axis/chartaxiselement_p.h
        axis/editableaxislabel.cpp axis/editableaxislabel_p.h
        axis/horizontalaxis.cpp axis/horizontalaxis_p.h
        axis/linearrowitem_p.h
        axis/logvalueaxis/chartlogvalueaxisx.cpp axis/logvalueaxis/chartlogvalueaxisx_p.h
        axis/logvalueaxis/chartlogvalueaxisy.cpp axis/logvalueaxis/chartlogvalueaxisy_p.h
        axis/logvalueaxis/polarchartlogvalueaxisangular.cpp axis/logvalueaxis/polarchartlogvalueaxisangular_p.h
        axis/logvalueaxis/polarchartlogvalueaxisradial.cpp axis/logvalueaxis/polarchartlogvalueaxisradial_p.h
        axis/logvalueaxis/qlogvalueaxis.cpp axis/logvalueaxis/qlogvalueaxis.h axis/logvalueaxis/qlogvalueaxis_p.h
        axis/polarchartaxis.cpp axis/polarchartaxis_p.h
        axis/polarchartaxisangular.cpp axis/polarchartaxisangular_p.h
        axis/polarchartaxisradial.cpp axis/polarchartaxisradial_p.h
        axis/qabstractaxis.cpp axis/qabstractaxis.h axis/qabstractaxis_p.h
        axis/valueaxis/chartvalueaxisx.cpp axis/valueaxis/chartvalueaxisx_p.h
        axis/valueaxis/chartvalueaxisy.cpp axis/valueaxis/chartvalueaxisy_p.h
        axis/valueaxis/polarchartvalueaxisangular.cpp axis/valueaxis/polarchartvalueaxisangular_p.h
        axis/valueaxis/polarchartvalueaxisradial.cpp axis/valueaxis/polarchartvalueaxisradial_p.h
        axis/valueaxis/qvalueaxis.cpp axis/valueaxis/qvalueaxis.h axis/valueaxis/qvalueaxis_p.h
        axis/valueaxis/valueaxislabel.cpp axis/valueaxis/valueaxislabel_p.h
        axis/verticalaxis.cpp axis/verticalaxis_p.h
        chartbackground.cpp chartbackground_p.h
        chartconfig_p.h
        chartdataset.cpp chartdataset_p.h
        chartelement.cpp chartelement_p.h
        charthelpers_p.h
        chartitem.cpp chartitem_p.h
        chartpresenter.cpp chartpresenter_p.h
        chartthememanager.cpp chartthememanager_p.h
        charttitle.cpp charttitle_p.h
        domain/abstractdomain.cpp domain/abstractdomain_p.h
        domain/logxlogydomain.cpp domain/logxlogydomain_p.h
        domain/logxlogypolardomain.cpp domain/logxlogypolardomain_p.h
        domain/logxydomain.cpp domain/logxydomain_p.h
        domain/logxypolardomain.cpp domain/logxypolardomain_p.h
        domain/polardomain.cpp domain/polardomain_p.h
        domain/xlogydomain.cpp domain/xlogydomain_p.h
        domain/xlogypolardomain.cpp domain/xlogypolardomain_p.h
        domain/xydomain.cpp domain/xydomain_p.h
        domain/xypolardomain.cpp domain/xypolardomain_p.h
        layout/abstractchartlayout.cpp layout/abstractchartlayout_p.h
        layout/cartesianchartlayout.cpp layout/cartesianchartlayout_p.h
        layout/polarchartlayout.cpp layout/polarchartlayout_p.h
        legend/legendlayout.cpp legend/legendlayout_p.h
        legend/legendmarkeritem.cpp legend/legendmarkeritem_p.h
        legend/legendscroller.cpp legend/legendscroller_p.h
        legend/legendmoveresizehandler.cpp legend/legendmoveresizehandler_p.h
        legend/qlegend.cpp legend/qlegend.h legend/qlegend_p.h
        legend/qlegendmarker.cpp legend/qlegendmarker.h legend/qlegendmarker_p.h
        legend/qxylegendmarker.cpp legend/qxylegendmarker.h legend/qxylegendmarker_p.h
        qabstractseries.cpp qabstractseries.h qabstractseries_p.h
        qchart.cpp qchart.h qchart_p.h
        qchartglobal.h qchartglobal_p.h
        qchartview.cpp qchartview.h qchartview_p.h
        qpolarchart.cpp qpolarchart.h
        scroller.cpp scroller_p.h
        themes/charttheme_p.h
        themes/chartthemebluecerulean_p.h
        themes/chartthemeblueicy_p.h
        themes/chartthemebluencs_p.h
        themes/chartthemebrownsand_p.h
        themes/chartthemedark_p.h
        themes/chartthemehighcontrast_p.h
        themes/chartthemelight_p.h
        themes/chartthemeqt_p.h
        themes/chartthemesystem_p.h
        xychart/glxyseriesdata.cpp xychart/glxyseriesdata_p.h
        xychart/qhxymodelmapper.cpp xychart/qhxymodelmapper.h
        xychart/qvxymodelmapper.cpp xychart/qvxymodelmapper.h
        xychart/qxymodelmapper.cpp xychart/qxymodelmapper.h xychart/qxymodelmapper_p.h
        xychart/qxyseries.cpp xychart/qxyseries.h xychart/qxyseries_p.h
        xychart/xychart.cpp xychart/xychart_p.h
    NO_PCH_SOURCES
        # these all contain Q_FOREACH, so need to undef QT_NO_FOREACH
        axis/barcategoryaxis/chartbarcategoryaxisx.cpp
        axis/barcategoryaxis/chartbarcategoryaxisy.cpp
        axis/barcategoryaxis/qbarcategoryaxis.cpp
        axis/cartesianchartaxis.cpp
        axis/categoryaxis/chartcategoryaxisx.cpp
        axis/categoryaxis/chartcategoryaxisy.cpp
        axis/chartaxiselement.cpp
        axis/logvalueaxis/chartlogvalueaxisx.cpp
        axis/logvalueaxis/chartlogvalueaxisy.cpp
        axis/polarchartaxis.cpp
        axis/polarchartaxisangular.cpp
        axis/polarchartaxisradial.cpp
        axis/valueaxis/chartvalueaxisx.cpp
        axis/valueaxis/chartvalueaxisy.cpp
        chartdataset.cpp
        chartpresenter.cpp
        chartthememanager.cpp
        layout/polarchartlayout.cpp
        legend/legendlayout.cpp
        legend/qlegend.cpp
        qchart.cpp
        xychart/glxyseriesdata.cpp
        xychart/qxyseries.cpp
        # end undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        animations
        axis
        axis/barcategoryaxis
        axis/categoryaxis
        axis/coloraxis
        axis/logvalueaxis
        axis/valueaxis
        domain
        layout
        legend
        themes
        xychart
    LIBRARIES
        Qt::CorePrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Widgets
    DEFINES
        QT_NO_CONTEXTLESS_CONNECT
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_opengl
    SOURCES
        glwidget.cpp glwidget_p.h
    NO_PCH_SOURCES
        glwidget.cpp # undef QT_NO_FOREACH
    PUBLIC_LIBRARIES
        Qt::OpenGL
        Qt::OpenGLWidgets
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_area_chart
    SOURCES
        areachart/areachartitem.cpp areachart/areachartitem_p.h
        areachart/qareaseries.cpp areachart/qareaseries.h areachart/qareaseries_p.h
        legend/qarealegendmarker.cpp legend/qarealegendmarker.h legend/qarealegendmarker_p.h
    INCLUDE_DIRECTORIES
        areachart
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_bar_chart
    SOURCES
        animations/baranimation.cpp animations/baranimation_p.h
        barchart/abstractbarchartitem.cpp barchart/abstractbarchartitem_p.h
        barchart/bar.cpp barchart/bar_p.h
        barchart/horizontal/bar/horizontalbarchartitem.cpp barchart/horizontal/bar/horizontalbarchartitem_p.h
        barchart/horizontal/bar/qhorizontalbarseries.cpp barchart/horizontal/bar/qhorizontalbarseries.h barchart/horizontal/bar/qhorizontalbarseries_p.h
        barchart/horizontal/percent/horizontalpercentbarchartitem.cpp barchart/horizontal/percent/horizontalpercentbarchartitem_p.h
        barchart/horizontal/percent/qhorizontalpercentbarseries.cpp barchart/horizontal/percent/qhorizontalpercentbarseries.h barchart/horizontal/percent/qhorizontalpercentbarseries_p.h
        barchart/horizontal/stacked/horizontalstackedbarchartitem.cpp barchart/horizontal/stacked/horizontalstackedbarchartitem_p.h
        barchart/horizontal/stacked/qhorizontalstackedbarseries.cpp barchart/horizontal/stacked/qhorizontalstackedbarseries.h barchart/horizontal/stacked/qhorizontalstackedbarseries_p.h
        barchart/qabstractbarseries.cpp barchart/qabstractbarseries.h barchart/qabstractbarseries_p.h
        barchart/qbarmodelmapper.cpp barchart/qbarmodelmapper.h barchart/qbarmodelmapper_p.h
        barchart/qbarset.cpp barchart/qbarset.h barchart/qbarset_p.h
        barchart/qhbarmodelmapper.cpp barchart/qhbarmodelmapper.h
        barchart/qvbarmodelmapper.cpp barchart/qvbarmodelmapper.h
        barchart/vertical/bar/barchartitem.cpp barchart/vertical/bar/barchartitem_p.h
        barchart/vertical/bar/qbarseries.cpp barchart/vertical/bar/qbarseries.h barchart/vertical/bar/qbarseries_p.h
        barchart/vertical/percent/percentbarchartitem.cpp barchart/vertical/percent/percentbarchartitem_p.h
        barchart/vertical/percent/qpercentbarseries.cpp barchart/vertical/percent/qpercentbarseries.h barchart/vertical/percent/qpercentbarseries_p.h
        barchart/vertical/stacked/qstackedbarseries.cpp barchart/vertical/stacked/qstackedbarseries.h barchart/vertical/stacked/qstackedbarseries_p.h
        barchart/vertical/stacked/stackedbarchartitem.cpp barchart/vertical/stacked/stackedbarchartitem_p.h
        legend/qbarlegendmarker.cpp legend/qbarlegendmarker.h legend/qbarlegendmarker_p.h
    NO_PCH_SOURCES
        barchart/abstractbarchartitem.cpp # undef QT_NO_FOREACH
        barchart/qabstractbarseries.cpp # undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        barchart
        barchart/horizontal/bar
        barchart/horizontal/percent
        barchart/horizontal/stacked
        barchart/vertical/bar
        barchart/vertical/percent
        barchart/vertical/stacked
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_line_chart
    SOURCES
        linechart/linechartitem.cpp linechart/linechartitem_p.h
        linechart/qlineseries.cpp linechart/qlineseries.h linechart/qlineseries_p.h
    INCLUDE_DIRECTORIES
        linechart
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_pie_chart
    SOURCES
        animations/pieanimation.cpp animations/pieanimation_p.h
        animations/piesliceanimation.cpp animations/piesliceanimation_p.h
        legend/qpielegendmarker.cpp legend/qpielegendmarker.h legend/qpielegendmarker_p.h
        piechart/piechartitem.cpp piechart/piechartitem_p.h
        piechart/pieslicedata_p.h
        piechart/piesliceitem.cpp piechart/piesliceitem_p.h
        piechart/qhpiemodelmapper.cpp piechart/qhpiemodelmapper.h
        piechart/qpiemodelmapper.cpp piechart/qpiemodelmapper.h piechart/qpiemodelmapper_p.h
        piechart/qpieseries.cpp piechart/qpieseries.h piechart/qpieseries_p.h
        piechart/qpieslice.cpp piechart/qpieslice.h piechart/qpieslice_p.h
        piechart/qvpiemodelmapper.cpp piechart/qvpiemodelmapper.h
    NO_PCH_SOURCES
        piechart/piechartitem.cpp # undef QT_NO_FOREACH
        piechart/qpieseries.cpp # undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        piechart
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_scatter_chart
    SOURCES
        animations/scatteranimation.cpp animations/scatteranimation_p.h
        scatterchart/qscatterseries.cpp scatterchart/qscatterseries.h scatterchart/qscatterseries_p.h
        scatterchart/scatterchartitem.cpp scatterchart/scatterchartitem_p.h
    INCLUDE_DIRECTORIES
        scatterchart
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_spline_chart
    SOURCES
        animations/splineanimation.cpp animations/splineanimation_p.h
        splinechart/qsplineseries.cpp splinechart/qsplineseries.h splinechart/qsplineseries_p.h
        splinechart/splinechartitem.cpp splinechart/splinechartitem_p.h
    INCLUDE_DIRECTORIES
        splinechart
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_boxplot_chart
    SOURCES
        animations/boxplotanimation.cpp animations/boxplotanimation_p.h
        animations/boxwhiskersanimation.cpp animations/boxwhiskersanimation_p.h
        boxplotchart/boxplotchartitem.cpp boxplotchart/boxplotchartitem_p.h
        boxplotchart/boxwhiskers.cpp boxplotchart/boxwhiskers_p.h
        boxplotchart/boxwhiskersdata_p.h
        boxplotchart/qboxplotmodelmapper.cpp boxplotchart/qboxplotmodelmapper.h boxplotchart/qboxplotmodelmapper_p.h
        boxplotchart/qboxplotseries.cpp boxplotchart/qboxplotseries.h boxplotchart/qboxplotseries_p.h
        boxplotchart/qboxset.cpp boxplotchart/qboxset.h boxplotchart/qboxset_p.h
        boxplotchart/qhboxplotmodelmapper.cpp boxplotchart/qhboxplotmodelmapper.h
        boxplotchart/qvboxplotmodelmapper.cpp boxplotchart/qvboxplotmodelmapper.h
        legend/qboxplotlegendmarker.cpp legend/qboxplotlegendmarker.h legend/qboxplotlegendmarker_p.h
    NO_PCH_SOURCES
        animations/boxplotanimation.cpp # undef QT_NO_FOREACH
        boxplotchart/boxplotchartitem.cpp # undef QT_NO_FOREACH
        boxplotchart/qboxplotseries.cpp # undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        boxplotchart
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_candlestick_chart
    SOURCES
        animations/candlestickanimation.cpp animations/candlestickanimation_p.h
        animations/candlestickbodywicksanimation.cpp animations/candlestickbodywicksanimation_p.h
        candlestickchart/candlestick.cpp candlestickchart/candlestick_p.h
        candlestickchart/candlestickchartitem.cpp candlestickchart/candlestickchartitem_p.h
        candlestickchart/candlestickdata_p.h
        candlestickchart/qcandlestickmodelmapper.cpp candlestickchart/qcandlestickmodelmapper.h candlestickchart/qcandlestickmodelmapper_p.h
        candlestickchart/qcandlestickseries.cpp candlestickchart/qcandlestickseries.h candlestickchart/qcandlestickseries_p.h
        candlestickchart/qcandlestickset.cpp candlestickchart/qcandlestickset.h candlestickchart/qcandlestickset_p.h
        candlestickchart/qhcandlestickmodelmapper.cpp candlestickchart/qhcandlestickmodelmapper.h
        candlestickchart/qvcandlestickmodelmapper.cpp candlestickchart/qvcandlestickmodelmapper.h
        legend/qcandlesticklegendmarker.cpp legend/qcandlesticklegendmarker.h legend/qcandlesticklegendmarker_p.h
    NO_PCH_SOURCES
        animations/candlestickanimation.cpp # undef QT_NO_FOREACH
        candlestickchart/candlestickchartitem.cpp # undef QT_NO_FOREACH
        candlestickchart/qcandlestickseries.cpp # undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        candlestickchart
)

#### Keys ignored in scope 12:.:.:charts.pro:MSVC:
# QMAKE_CXXFLAGS_WARN_ON = "-wd4267"

qt_internal_extend_target(Charts CONDITION WIN32
    PUBLIC_LIBRARIES
        user32
)

qt_internal_extend_target(Charts CONDITION QT_FEATURE_charts_datetime_axis
    SOURCES
        axis/datetimeaxis/chartdatetimeaxisx.cpp axis/datetimeaxis/chartdatetimeaxisx_p.h
        axis/datetimeaxis/chartdatetimeaxisy.cpp axis/datetimeaxis/chartdatetimeaxisy_p.h
        axis/datetimeaxis/datetimeaxislabel.cpp axis/datetimeaxis/datetimeaxislabel_p.h
        axis/datetimeaxis/polarchartdatetimeaxisangular.cpp axis/datetimeaxis/polarchartdatetimeaxisangular_p.h
        axis/datetimeaxis/polarchartdatetimeaxisradial.cpp axis/datetimeaxis/polarchartdatetimeaxisradial_p.h
        axis/datetimeaxis/qdatetimeaxis.cpp axis/datetimeaxis/qdatetimeaxis.h axis/datetimeaxis/qdatetimeaxis_p.h
    NO_PCH_SOURCES
        axis/datetimeaxis/chartdatetimeaxisx.cpp # undef QT_NO_FOREACH
        axis/datetimeaxis/chartdatetimeaxisy.cpp # undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        axis/datetimeaxis
)
qt_internal_add_docs(Charts
    doc/qtcharts.qdocconf
)


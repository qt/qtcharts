# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(chartsgallery LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/chartsgallery")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(chartsgallery
    areawidget.cpp areawidget.h
    barmodelmappermodel.cpp barmodelmappermodel.h
    barmodelmapperwidget.cpp barmodelmapperwidget.h
    boxplotdatareader.cpp boxplotdatareader.h
    boxplotwidget.cpp boxplotwidget.h
    barwidget.cpp barwidget.h
    barpercentwidget.cpp barpercentwidget.h
    barstackedwidget.cpp barstackedwidget.h
    callout.cpp callout.h
    calloutwidget.cpp calloutwidget.h
    calloutview.cpp calloutview.h
    candlestickwidget.cpp candlestickwidget.h
    candlestickdatareader.cpp candlestickdatareader.h
    contentwidget.cpp contentwidget.h
    customchartwidget.cpp customchartwidget.h
    datetimeaxiswidget.cpp datetimeaxiswidget.h
    donutbreakdownchart.cpp donutbreakdownchart.h
    donutbreakdownmainslice.cpp donutbreakdownmainslice.h
    donutbreakdownwidget.cpp donutbreakdownwidget.h
    donutwidget.cpp donutwidget.h
    dynamicsplinewidget.cpp dynamicsplinewidget.h
    horizontalbarwidget.cpp horizontalbarwidget.h
    horizontalpercentbarwidget.cpp horizontalpercentbarwidget.h
    horizontalstackedbarwidget.cpp horizontalstackedbarwidget.h
    interactionswidget.cpp interactionswidget.h
    interactionsview.cpp interactionsview.h
    interactionschart.cpp interactionschart.h
    legendwidget.cpp legendwidget.h
    legendmarkerswidget.cpp legendmarkerswidget.h
    lightmarkerswidget.cpp lightmarkerswidget.h
    lineandbarwidget.cpp lineandbarwidget.h
    linewidget.cpp linewidget.h
    logaxiswidget.cpp logaxiswidget.h
    modeldatamodel.cpp modeldatamodel.h
    modeldatawidget.cpp modeldatawidget.h
    multiaxiswidget.cpp multiaxiswidget.h
    nesteddonutswidget.cpp nesteddonutswidget.h
    main.cpp
    mainwidget.cpp mainwidget.h
    pccpentool.cpp pccpentool.h
    pccbrushtool.cpp pccbrushtool.h
    pcccustomslice.cpp pcccustomslice.h
    pccwidget.cpp pccwidget.h
    piedrilldownchart.cpp piedrilldownchart.h
    piedrilldownslice.cpp piedrilldownslice.h
    piedrilldownwidget.cpp piedrilldownwidget.h
    piewidget.cpp piewidget.h
    pointconfigurationwidget.cpp pointconfigurationwidget.h
    polarchartview.cpp polarchartview.h
    polarchartwidget.cpp polarchartwidget.h
    scatterinteractionswidget.cpp scatterinteractionswidget.h
    scatterwidget.cpp scatterwidget.h
    selectedbarwidget.cpp selectedbarwidget.h
    splinewidget.cpp splinewidget.h
    stackeddrilldownchart.cpp stackeddrilldownchart.h
    stackeddrilldownseries.cpp stackeddrilldownseries.h
    stackeddrilldownwidget.cpp stackeddrilldownwidget.h
    temperaturerecordswidget.cpp temperaturerecordswidget.h
    themewidget.cpp themewidget.h themewidget.ui
)

set_target_properties(chartsgallery PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chartsgallery PRIVATE
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

set_source_files_properties("data/boxplot_a.txt"
    PROPERTIES QT_RESOURCE_ALIAS "boxplot_a"
)

set_source_files_properties("data/boxplot_b.txt"
    PROPERTIES QT_RESOURCE_ALIAS "boxplot_b"
)

set_source_files_properties("data/candlestick.txt"
    PROPERTIES QT_RESOURCE_ALIAS "candlestick"
)

set_source_files_properties("data/sun_spots.txt"
    PROPERTIES QT_RESOURCE_ALIAS "sun_spots"
)

set_source_files_properties("data/blue_triangle.png"
    PROPERTIES QT_RESOURCE_ALIAS "blue_triangle"
)

set_source_files_properties("data/green_triangle.png"
    PROPERTIES QT_RESOURCE_ALIAS "green_triangle"
)

set(chartsgallery_resource_files
    "data/boxplot_a.txt"
    "data/boxplot_b.txt"
    "data/candlestick.txt"
    "data/sun_spots.txt"
    "data/blue_triangle.png"
    "data/green_triangle.png"
)

qt6_add_resources(chartsgallery "chartsgallery"
    PREFIX
        "/"
    FILES
        ${chartsgallery_resource_files}
)

install(TARGETS chartsgallery
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

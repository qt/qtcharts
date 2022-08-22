# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(candlestickchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/candlestickchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(candlestickchart
    candlestickdatareader.cpp candlestickdatareader.h
    main.cpp
)

set_target_properties(candlestickchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(candlestickchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

# Resources:
set_source_files_properties("acme_data.txt"
    PROPERTIES QT_RESOURCE_ALIAS "acme"
)

set(candlestickdata_resource_files
    "acme_data.txt"
)

qt6_add_resources(candlestickchart "candlestickdata"
    PREFIX
        "/"
    FILES
        ${candlestickdata_resource_files}
)

install(TARGETS candlestickchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

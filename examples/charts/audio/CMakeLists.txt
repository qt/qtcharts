# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(audio LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/audio")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Multimedia)

qt_standard_project_setup()

qt_add_executable(audio
    main.cpp
    widget.cpp widget.h
    xyseriesiodevice.cpp xyseriesiodevice.h
)

set_target_properties(audio PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/apple/Info.cmake.plist"
)

target_link_libraries(audio PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Multimedia
)

install(TARGETS audio
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from qml-qtquicktest.pro.

#####################################################################
## qml-qtquicktest Test:
#####################################################################

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_qml-qtquicktest LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

file(GLOB_RECURSE test_data_glob
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    data/*)
list(APPEND test_data ${test_data_glob})

qt_internal_add_test(tst_qml-qtquicktest
    QMLTEST
    SOURCES
        ../inc/tst_definitions.h
        main.cpp
    DEFINES
        QUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
    INCLUDE_DIRECTORIES
        ../inc
    LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
    TESTDATA ${test_data}
)

#### Keys ignored in scope 1:.:.:qml-qtquicktest.pro:<TRUE>:
# OTHER_FILES = "tst_*.qml"
# TEMPLATE = "app"

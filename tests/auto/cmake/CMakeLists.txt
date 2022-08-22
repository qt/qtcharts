# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# This is an automatic test for the CMake configuration files.
# To run it manually,
# 1) mkdir build   # Create a build directory
# 2) cd build
# 3) # Run cmake on this directory
#    `$qt_prefix/bin/qt-cmake ..` or `cmake -DCMAKE_PREFIX_PATH=/path/to/qt ..`
# 4) ctest         # Run ctest

cmake_minimum_required(VERSION 3.16)
project(charts_cmake_tests)
enable_testing()

set(required_packages Core Charts)

# Setup the test when called as a completely standalone project.
if(TARGET Qt6::Core)
    # Tests are built as part of the repository's build tree.
    # Setup paths so that the Qt packages are found.
    qt_internal_set_up_build_dir_package_paths()
endif()

find_package(Qt6 REQUIRED COMPONENTS ${required_packages})

# Setup common test variables which were previously set by ctest_testcase_common.prf.
set(CMAKE_MODULES_UNDER_TEST "${required_packages}")

foreach(qt_package ${CMAKE_MODULES_UNDER_TEST})
    set(package_name "${QT_CMAKE_EXPORT_NAMESPACE}${qt_package}")
    if(${package_name}_FOUND)
        set(CMAKE_${qt_package}_MODULE_MAJOR_VERSION "${${package_name}_VERSION_MAJOR}")
        set(CMAKE_${qt_package}_MODULE_MINOR_VERSION "${${package_name}_VERSION_MINOR}")
        set(CMAKE_${qt_package}_MODULE_PATCH_VERSION "${${package_name}_VERSION_PATCH}")
    endif()
endforeach()

include("${_Qt6CTestMacros}")

set(module_includes
    Charts QChartView
)

_qt_internal_test_module_includes(
     ${module_includes}
)

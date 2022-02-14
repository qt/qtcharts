cmake_minimum_required(VERSION 3.16)
project(horizontalstackedbarchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/horizontalstackedbarchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(horizontalstackedbarchart
    main.cpp
)

set_target_properties(horizontalstackedbarchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(horizontalstackedbarchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS horizontalstackedbarchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

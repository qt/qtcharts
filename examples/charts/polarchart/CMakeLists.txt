cmake_minimum_required(VERSION 3.16)
project(polarchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/polarchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(polarchart
    chartview.cpp chartview.h
    main.cpp
)

set_target_properties(polarchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(polarchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS polarchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

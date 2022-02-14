cmake_minimum_required(VERSION 3.16)
project(percentbarchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/percentbarchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(percentbarchart
    main.cpp
)

set_target_properties(percentbarchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(percentbarchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS percentbarchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

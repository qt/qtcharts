cmake_minimum_required(VERSION 3.16)
project(customchart LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/customchart")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(customchart
    main.cpp
)

set_target_properties(customchart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(customchart PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS customchart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

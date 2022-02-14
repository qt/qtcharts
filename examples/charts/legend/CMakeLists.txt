cmake_minimum_required(VERSION 3.16)
project(legend LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/legend")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(legend
    main.cpp
    mainwidget.cpp mainwidget.h
)

set_target_properties(legend PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(legend PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS legend
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

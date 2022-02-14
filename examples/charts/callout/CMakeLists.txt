cmake_minimum_required(VERSION 3.16)
project(callout LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/callout")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(callout
    callout.cpp callout.h
    main.cpp
    view.cpp view.h
)

set_target_properties(callout PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(callout PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS callout
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

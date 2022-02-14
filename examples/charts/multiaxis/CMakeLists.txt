cmake_minimum_required(VERSION 3.16)
project(multiaxis LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/multiaxis")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(multiaxis
    main.cpp
)

set_target_properties(multiaxis PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(multiaxis PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS multiaxis
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

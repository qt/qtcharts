cmake_minimum_required(VERSION 3.16)
project(temperaturerecords LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/temperaturerecords")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(temperaturerecords
    main.cpp
)

set_target_properties(temperaturerecords PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(temperaturerecords PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS temperaturerecords
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

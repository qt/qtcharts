cmake_minimum_required(VERSION 3.16)
project(piechartcustomization LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts/piechartcustomization")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui)

qt_add_executable(piechartcustomization
    brushtool.cpp brushtool.h
    customslice.cpp customslice.h
    main.cpp
    mainwidget.cpp mainwidget.h
    pentool.cpp pentool.h
)

set_target_properties(piechartcustomization PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(piechartcustomization PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

install(TARGETS piechartcustomization
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

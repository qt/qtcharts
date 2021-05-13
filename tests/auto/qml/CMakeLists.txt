# Generated from qml.pro.

#####################################################################
## qml Test:
#####################################################################

qt_internal_add_test(charts_qml
    SOURCES
        ../inc/tst_definitions.h
        tst_qml.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::Widgets
)

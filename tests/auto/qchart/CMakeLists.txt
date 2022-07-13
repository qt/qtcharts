# Generated from qchart.pro.

#####################################################################
## qchart Test:
#####################################################################

qt_internal_add_test(tst_qchart
    SOURCES
        ../inc/tst_definitions.h
        tst_qchart.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

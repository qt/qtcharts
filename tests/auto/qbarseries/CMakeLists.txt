# Generated from qbarseries.pro.

#####################################################################
## qbarseries Test:
#####################################################################

qt_internal_add_test(tst_qbarseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qbarseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

# Generated from qpieslice.pro.

#####################################################################
## qpieslice Test:
#####################################################################

qt_internal_add_test(tst_qpieslice
    SOURCES
        ../inc/tst_definitions.h
        tst_qpieslice.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

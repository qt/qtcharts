# Generated from qpiemodelmapper.pro.

#####################################################################
## qpiemodelmapper Test:
#####################################################################

qt_internal_add_test(tst_qpiemodelmapper
    SOURCES
        ../inc/tst_definitions.h
        tst_qpiemodelmapper.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

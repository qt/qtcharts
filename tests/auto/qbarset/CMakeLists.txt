# Generated from qbarset.pro.

#####################################################################
## qbarset Test:
#####################################################################

qt_internal_add_test(tst_qbarset
    SOURCES
        ../inc/tst_definitions.h
        tst_qbarset.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

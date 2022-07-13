# Generated from qareaseries.pro.

#####################################################################
## qareaseries Test:
#####################################################################

qt_internal_add_test(tst_qareaseries
    SOURCES
        ../inc/tst_definitions.h
        tst_qareaseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

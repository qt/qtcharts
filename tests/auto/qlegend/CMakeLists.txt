# Generated from qlegend.pro.

#####################################################################
## qlegend Test:
#####################################################################

qt_internal_add_test(qlegend
    SOURCES
        ../inc/tst_definitions.h
        tst_qlegend.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

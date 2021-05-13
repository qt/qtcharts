# Generated from presenterchart.pro.

#####################################################################
## presenterchart Binary:
#####################################################################

qt_internal_add_manual_test(presenterchart
    GUI
    SOURCES
        chartview.cpp chartview.h
        main.cpp
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

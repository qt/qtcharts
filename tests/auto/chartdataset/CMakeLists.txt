# Generated from chartdataset.pro.

#####################################################################
## chartdataset Test:
#####################################################################

qt_internal_add_test(tst_chartdataset
    SOURCES
        ../inc/tst_definitions.h
        tst_chartdataset.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::ChartsPrivate
        Qt::CorePrivate
        Qt::Gui
        Qt::Widgets
)

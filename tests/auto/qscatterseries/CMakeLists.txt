# Generated from qscatterseries.pro.

#####################################################################
## qscatterseries Test:
#####################################################################

qt_internal_add_test(tst_qscatterseries
    SOURCES
        ../inc/tst_definitions.h
        ../qxyseries/tst_qxyseries.cpp ../qxyseries/tst_qxyseries.h
        tst_qscatterseries.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

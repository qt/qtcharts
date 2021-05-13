# Generated from candlesticktester.pro.

#####################################################################
## candlesticktester Binary:
#####################################################################

qt_internal_add_manual_test(candlesticktester
    GUI
    SOURCES
        customtablemodel.cpp customtablemodel.h
        main.cpp
        mainwidget.cpp mainwidget.h
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

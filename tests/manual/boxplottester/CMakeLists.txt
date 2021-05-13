# Generated from boxplottester.pro.

#####################################################################
## boxplottester Binary:
#####################################################################

qt_internal_add_manual_test(boxplottester
    GUI
    SOURCES
        customtablemodel.cpp customtablemodel.h
        main.cpp
        mainwidget.cpp mainwidget.h
        pentool.cpp pentool.h
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:boxplottester.pro:<TRUE>:
# TEMPLATE = "app"

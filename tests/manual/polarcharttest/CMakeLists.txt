# Generated from polarcharttest.pro.

#####################################################################
## polarcharttest Binary:
#####################################################################

qt_internal_add_manual_test(polarcharttest
    GUI
    SOURCES
        chartview.cpp chartview.h
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
    INCLUDE_DIRECTORIES
        .
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)

#### Keys ignored in scope 1:.:.:polarcharttest.pro:<TRUE>:
# TEMPLATE = "app"

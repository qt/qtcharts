# Generated from demoLauncher.pro.

#####################################################################
## demoLauncher Binary:
#####################################################################

qt_internal_add_executable(demoLauncher
    GUI
    SOURCES
        graphicsbutton.cpp graphicsbutton.h
        main.cpp
        widget.cpp widget.h
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Widgets
)

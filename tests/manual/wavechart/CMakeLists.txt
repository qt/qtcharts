# Generated from wavechart.pro.

#####################################################################
## wavechart Binary:
#####################################################################

qt_internal_add_manual_test(wavechart
    GUI
    SOURCES
        main.cpp
        wavechart.cpp wavechart.h
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
)

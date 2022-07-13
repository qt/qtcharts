# Generated from qlogvalueaxis.pro.

#####################################################################
## qlogvalueaxis Test:
#####################################################################

qt_internal_add_test(tst_qlogvalueaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qlogvalueaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

# Generated from qcategoryaxis.pro.

#####################################################################
## qcategoryaxis Test:
#####################################################################

qt_internal_add_test(tst_qcategoryaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qcategoryaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

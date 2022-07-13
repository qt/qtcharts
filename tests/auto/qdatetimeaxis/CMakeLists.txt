# Generated from qdatetimeaxis.pro.

#####################################################################
## qdatetimeaxis Test:
#####################################################################

qt_internal_add_test(tst_qdatetimeaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qdatetimeaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

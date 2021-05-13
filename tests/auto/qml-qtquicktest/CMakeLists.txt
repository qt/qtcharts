# Generated from qml-qtquicktest.pro.

#####################################################################
## qml-qtquicktest Test:
#####################################################################

qt_internal_add_test(qml-qtquicktest
    QMLTEST
    SOURCES
        ../inc/tst_definitions.h
        main.cpp
    DEFINES
        QUICK_TEST_SOURCE_DIR=\"\\\"${CMAKE_CURRENT_SOURCE_DIR}\\\"\"
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::Widgets
)

#### Keys ignored in scope 1:.:.:qml-qtquicktest.pro:<TRUE>:
# OTHER_FILES = "tst_*.qml"
# TEMPLATE = "app"

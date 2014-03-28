!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

DESTDIR = $$CHART_BUILD_BIN_DIR
!ios {
OBJECTS_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
MOC_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
UI_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
RCC_DIR = $$CHART_BUILD_DIR/demos/$$TARGET
}
TEMPLATE = app
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# staticlib config causes problems when building executables
staticlib: CONFIG-=staticlib

android {
    # Workaround to fix android deployment, which seems to always look for target in
    # OUT_PWD instead of DESTDIR.
    COPY_PARAMETERS = "$$CHART_BUILD_BIN_DIR/lib$${TARGET}.so $$OUT_PWD/lib$${TARGET}.so"
    contains(QMAKE_HOST.os, Windows): COPY_PARAMETERS = $$replace(COPY_PARAMETERS, "/","\\")
    QMAKE_POST_LINK += $$QMAKE_COPY $$COPY_PARAMETERS

    contains(TARGET, qml.*) {
        charts_qmldir.files = $$CHART_BUILD_QML_PLUGIN_DIR/qmldir
        charts_qmldir.path = /assets/imports/QtCommercial/Chart
        charts_qmlplugin.files = $$CHART_BUILD_QML_PLUGIN_DIR/libqtcommercialchartqml.so
        charts_qmlplugin.path = /libs/$$ANDROID_TARGET_ARCH
        INSTALLS += charts_qmldir charts_qmlplugin
    } else:contains(TARGET, quick2.*) {
        charts_qmldir.files = $$CHART_BUILD_QML2_PLUGIN_DIR/qmldir
        charts_qmldir.path = /assets/qml/QtCommercial/Chart
        charts_qmlplugin.files = $$CHART_BUILD_QML2_PLUGIN_DIR/libqtcommercialchartqml2.so
        charts_qmlplugin.path = /libs/$$ANDROID_TARGET_ARCH
        INSTALLS += charts_qmldir charts_qmlplugin
    }
}

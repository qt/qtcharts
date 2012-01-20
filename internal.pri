integrated_build:{
    message('Internal build within charts core source tree')
    INCLUDEPATH += $$CHART_BUILD_HEADER_DIR
    LIBS += -L $$CHART_BUILD_LIB_DIR -Wl,-rpath,$$CHART_BUILD_LIB_DIR
    DESTDIR = $$CHART_BUILD_BIN_DIR
    CONFIG(debug, debug|release) {
    LIBS += -lQtCommercialChartd

    #this is ugly hack to work around missing rpath, it simply copies lib
    win32:{
        copylib.target = $$CHART_BUILD_BIN_DIR/QtCommercialChartd.dll
        copylib.commands = $$QMAKE_COPY $$CHART_BUILD_LIB_DIR\QtCommercialChartd.dll $$CHART_BUILD_BIN_DIR
        copylib.depends = $$CHART_BUILD_LIB_DIR/QtCommercialChartd.dll
        PRE_TARGETDEPS += $$CHART_BUILD_BIN_DIR/QtCommercialChartd.dll
        QMAKE_EXTRA_TARGETS +=copylib
    }

    } else {
    LIBS += -lQtCommercialChart

    #this is ugly hack to work around missing rpath, it simply copies lib
    win32:{
        copylib.target = $$CHART_BUILD_BIN_DIR/QtCommercialChart
        copylib.commands = $$QMAKE_COPY $$CHART_BUILD_LIB_DIR\QtCommercialChart.dll $$CHART_BUILD_BIN_DIR
        copylib.depends = $$CHART_BUILD_LIB_DIR/QtCommercialChart.dll
        PRE_TARGETDEPS += $$CHART_BUILD_BIN_DIR/QtCommercialChart
        QMAKE_EXTRA_TARGETS +=copylib
        }
    }
}else{
    CONFIG+=qtcommercialchart
}

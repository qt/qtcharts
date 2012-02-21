integrated_build:{
    message('Running integrated build against local libs...')
    INCLUDEPATH += $$CHART_BUILD_PUBLIC_HEADER_DIR

    !win32: {
        LIBS += -L $$CHART_BUILD_LIB_DIR -Wl,-rpath,$$CHART_BUILD_LIB_DIR
    }else{
        win32-msvc*: {
            # hack fix for error:
            #   "LINK : fatal error LNK1146: no argument specified with option '/LIBPATH:'"
            QMAKE_LIBDIR += $$CHART_BUILD_LIB_DIR
        }else{
            LIBS += -L $$CHART_BUILD_LIB_DIR
        }
    }

    CONFIG(debug, debug|release) {
        LIBS += -lQtCommercialChartd
        #this is ugly hack to work around missing rpath, it simply copies lib
        win32:{
            copylib.target = $$CHART_BUILD_BIN_DIR/QtCommercialChartd.dll
            copylib.commands = $$QMAKE_COPY $$CHART_BUILD_LIB_DIR\\QtCommercialChartd.dll $$CHART_BUILD_BIN_DIR
            copylib.depends = $$CHART_BUILD_LIB_DIR/QtCommercialChartd.dll
            PRE_TARGETDEPS += $$CHART_BUILD_BIN_DIR/QtCommercialChartd.dll
            QMAKE_EXTRA_TARGETS +=copylib
        }
    } else {
        LIBS += -lQtCommercialChart

        #this is ugly hack to work around missing rpath, it simply copies lib
        win32: {
            copylib.target = $$CHART_BUILD_BIN_DIR/QtCommercialChart
            copylib.commands = $$QMAKE_COPY $$CHART_BUILD_LIB_DIR\\QtCommercialChart.dll $$CHART_BUILD_BIN_DIR
            copylib.depends = $$CHART_BUILD_LIB_DIR/QtCommercialChart.dll
            PRE_TARGETDEPS += $$CHART_BUILD_BIN_DIR/QtCommercialChart
            QMAKE_EXTRA_TARGETS +=copylib
        }
    }

    mac: {
        # This is a hack to make binaries to use the internal version of the QtCommercial Charts library on OSX
        QMAKE_POST_LINK += install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/chartwidgettest.app/Contents/MacOS/chartwidgettest
        QMAKE_POST_LINK += && install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/barchart.app/Contents/MacOS/barchart
        QMAKE_POST_LINK += && install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/colorlineChart.app/Contents/MacOS/colorlineChart
        QMAKE_POST_LINK += && install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/lineChart.app/Contents/MacOS/lineChart
        QMAKE_POST_LINK += && install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/percentbarchart.app/Contents/MacOS/percentbarchart
        QMAKE_POST_LINK += && install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/stackedbarchart.app/Contents/MacOS/stackedbarchart
        QMAKE_POST_LINK += && install_name_tool -change "libQtCommercialChartd.1.dylib" "@rpath/libQtCommercialChartd.dylib" $$CHART_BUILD_BIN_DIR/zoomLineChart.app/Contents/MacOS/zoomLineChart
    }

} else {
    message('Running build aginst system libs...')
    CONFIG+=qtcommercialchart
}

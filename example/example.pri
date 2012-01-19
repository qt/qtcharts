build_examples:{
    message('Internal build within charts core source tree')
    INCLUDEPATH += $$CHART_BUILD_HEADER_DIR
    LIBS += -L $$CHART_BUILD_LIB_DIR -Wl,-rpath,$$CHART_BUILD_LIB_DIR
    DESTDIR = $$CHART_BUILD_BIN
    CONFIG(debug, debug|release) {
    LIBS += -lQtCommercialChartd
} else {
    LIBS += -lQtCommercialChart
}

}

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/axisanimation.cpp \
    $$PWD/xyanimation.cpp \
    $$PWD/chartanimation.cpp

HEADERS += \
    $$PWD/axisanimation_p.h \
    $$PWD/chartanimation_p.h \
    $$PWD/xyanimation_p.h

qtConfig(charts-spline-chart) {
    SOURCES += $$PWD/splineanimation.cpp
    HEADERS += $$PWD/splineanimation_p.h
}
qtConfig(charts-scatter-chart) {
    SOURCES += $$PWD/scatteranimation.cpp
    HEADERS += $$PWD/scatteranimation_p.h
}
qtConfig(charts-pie-chart) {
    SOURCES += $$PWD/pieanimation.cpp \
        $$PWD/piesliceanimation.cpp
    HEADERS += $$PWD/pieanimation_p.h \
        $$PWD/piesliceanimation_p.h
}
qtConfig(charts-bar-chart) {
    SOURCES += $$PWD/baranimation.cpp
    HEADERS += $$PWD/baranimation_p.h
}
qtConfig(charts-boxplot-chart) {
    SOURCES += $$PWD/boxplotanimation.cpp \
    $$PWD/boxwhiskersanimation.cpp
    HEADERS += $$PWD/boxplotanimation_p.h \
        $$PWD/boxwhiskersanimation_p.h

}
qtConfig(charts-candlestick-chart) {
    SOURCES += $$PWD/candlestickanimation.cpp \
        $$PWD/candlestickbodywicksanimation.cpp
    HEADERS += $$PWD/candlestickanimation_p.h \
        $$PWD/candlestickbodywicksanimation_p.h
}

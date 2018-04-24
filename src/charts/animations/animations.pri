INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/axisanimation.cpp \
    $$PWD/xyanimation.cpp \
    $$PWD/chartanimation.cpp

PRIVATE_HEADERS += \
    $$PWD/axisanimation_p.h \
    $$PWD/chartanimation_p.h \
    $$PWD/xyanimation_p.h

qtConfig(charts-spline-chart) {
    SOURCES += $$PWD/splineanimation.cpp
    PRIVATE_HEADERS += $$PWD/splineanimation_p.h
}
qtConfig(charts-scatter-chart) {
    SOURCES += $$PWD/scatteranimation.cpp
    PRIVATE_HEADERS += $$PWD/scatteranimation_p.h
}
qtConfig(charts-pie-chart) {
    SOURCES += $$PWD/pieanimation.cpp \
        $$PWD/piesliceanimation.cpp
    PRIVATE_HEADERS += $$PWD/pieanimation_p.h \
        $$PWD/piesliceanimation_p.h
}
qtConfig(charts-bar-chart) {
    SOURCES += $$PWD/baranimation.cpp
    PRIVATE_HEADERS += $$PWD/baranimation_p.h
}
qtConfig(charts-boxplot-chart) {
    SOURCES += $$PWD/boxplotanimation.cpp \
    $$PWD/boxwhiskersanimation.cpp
    PRIVATE_HEADERS += $$PWD/boxplotanimation_p.h \
        $$PWD/boxwhiskersanimation_p.h

}
qtConfig(charts-candlestick-chart) {
    SOURCES += $$PWD/candlestickanimation.cpp \
        $$PWD/candlestickbodywicksanimation.cpp
    PRIVATE_HEADERS += $$PWD/candlestickanimation_p.h \
        $$PWD/candlestickbodywicksanimation_p.h
}

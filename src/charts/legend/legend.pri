INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qlegend.cpp \
    $$PWD/legendlayout.cpp \
    $$PWD/qlegendmarker.cpp \
    $$PWD/legendmarkeritem.cpp \
    $$PWD/qxylegendmarker.cpp \
    $$PWD/legendscroller.cpp

HEADERS += \
    $$PWD/legendscroller_p.h \
    $$PWD/qlegend_p.h  \
    $$PWD/legendlayout_p.h \
    $$PWD/qlegendmarker_p.h \
    $$PWD/legendmarkeritem_p.h \
    $$PWD/qxylegendmarker_p.h

HEADERS += \
    $$PWD/qlegend.h \
    $$PWD/qlegendmarker.h \
    $$PWD/qxylegendmarker.h

qtConfig(charts-area-chart) {
    HEADERS += $$PWD/qarealegendmarker_p.h
    HEADERS += $$PWD/qarealegendmarker.h
    SOURCES += $$PWD/qarealegendmarker.cpp
}
qtConfig(charts-pie-chart) {
    HEADERS += $$PWD/qpielegendmarker_p.h
    HEADERS += $$PWD/qpielegendmarker.h
    SOURCES +=  $$PWD/qpielegendmarker.cpp
}
qtConfig(charts-bar-chart) {
    HEADERS += $$PWD/qbarlegendmarker_p.h
    HEADERS += $$PWD/qbarlegendmarker.h
    SOURCES +=  $$PWD/qbarlegendmarker.cpp
}
qtConfig(charts-boxplot-chart) {
    HEADERS += $$PWD/qboxplotlegendmarker_p.h
    HEADERS += $$PWD/qboxplotlegendmarker.h
    SOURCES += $$PWD/qboxplotlegendmarker.cpp
}
qtConfig(charts-candlestick-chart) {
    HEADERS += $$PWD/qcandlesticklegendmarker_p.h
    HEADERS += $$PWD/qcandlesticklegendmarker.h
    SOURCES += $$PWD/qcandlesticklegendmarker.cpp
}

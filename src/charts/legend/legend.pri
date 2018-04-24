INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qlegend.cpp \
    $$PWD/legendlayout.cpp \
    $$PWD/qlegendmarker.cpp \
    $$PWD/legendmarkeritem.cpp \
    $$PWD/qxylegendmarker.cpp \
    $$PWD/legendscroller.cpp

PRIVATE_HEADERS += \
    $$PWD/legendscroller_p.h \
    $$PWD/qlegend_p.h  \
    $$PWD/legendlayout_p.h \
    $$PWD/qlegendmarker_p.h \
    $$PWD/legendmarkeritem_p.h \
    $$PWD/qxylegendmarker_p.h

PUBLIC_HEADERS += \
    $$PWD/qlegend.h \
    $$PWD/qlegendmarker.h \
    $$PWD/qxylegendmarker.h

qtConfig(charts-area-chart) {
    PRIVATE_HEADERS += $$PWD/qarealegendmarker_p.h
    PUBLIC_HEADERS += $$PWD/qarealegendmarker.h
    SOURCES += $$PWD/qarealegendmarker.cpp
}
qtConfig(charts-pie-chart) {
    PRIVATE_HEADERS += $$PWD/qpielegendmarker_p.h
    PUBLIC_HEADERS += $$PWD/qpielegendmarker.h
    SOURCES +=  $$PWD/qpielegendmarker.cpp
}
qtConfig(charts-bar-chart) {
    PRIVATE_HEADERS += $$PWD/qbarlegendmarker_p.h
    PUBLIC_HEADERS += $$PWD/qbarlegendmarker.h
    SOURCES +=  $$PWD/qbarlegendmarker.cpp
}
qtConfig(charts-boxplot-chart) {
    PRIVATE_HEADERS += $$PWD/qboxplotlegendmarker_p.h
    PUBLIC_HEADERS += $$PWD/qboxplotlegendmarker.h
    SOURCES += $$PWD/qboxplotlegendmarker.cpp
}
qtConfig(charts-candlestick-chart) {
    PRIVATE_HEADERS += $$PWD/qcandlesticklegendmarker_p.h
    PUBLIC_HEADERS += $$PWD/qcandlesticklegendmarker.h
    SOURCES += $$PWD/qcandlesticklegendmarker.cpp
}

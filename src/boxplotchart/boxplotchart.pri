INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/boxplotchartitem.cpp \
    $$PWD/qboxplotseries.cpp \
    $$PWD/boxwhiskers.cpp

PRIVATE_HEADERS += \
    $$PWD/boxplotchartitem_p.h \
    $$PWD/qboxplotseries_p.h \
    $$PWD/boxwhiskers_p.h \
    $$PWD/boxwhiskersdata_p.h

PUBLIC_HEADERS += \
    $$PWD/qboxplotseries.h

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/boxplotchartitem.cpp \
    $$PWD/qboxplotseries.cpp \
    $$PWD/boxwhiskers.cpp \
    $$PWD/qboxset.cpp

PRIVATE_HEADERS += \
    $$PWD/boxplotchartitem_p.h \
    $$PWD/qboxplotseries_p.h \
    $$PWD/boxwhiskers_p.h \
    $$PWD/boxwhiskersdata_p.h \
    $$PWD/qboxset_p.h

PUBLIC_HEADERS += \
    $$PWD/qboxplotseries.h \
    $$PWD/qboxset.h

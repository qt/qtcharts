INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qpieseries.cpp \
    $$PWD/pieslice.cpp \
    $$PWD/piechartitem.cpp \
    $$PWD/qpieslice.cpp

PRIVATE_HEADERS += \
    $$PWD/piechartitem_p.h \
    $$PWD/pieslice_p.h \

PUBLIC_HEADERS += \
    $$PWD/qpieseries.h \
    $$PWD/qpieslice.h

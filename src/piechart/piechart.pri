INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qpieseries.cpp \
    $$PWD/piesliceitem.cpp \
    $$PWD/piechartitem.cpp \
    $$PWD/qpieslice.cpp

PRIVATE_HEADERS += \
    $$PWD/pieslicedata_p.h \
    $$PWD/piechartitem_p.h \
    $$PWD/piesliceitem_p.h \
    $$PWD/qpieseriesprivate_p.h

PUBLIC_HEADERS += \
    $$PWD/qpieseries.h \
    $$PWD/qpieslice.h

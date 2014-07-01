#INCLUDEPATH += $$PWD
#DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/xychart.cpp \
    $$PWD/qxyseries.cpp \
    $$PWD/qxymodelmapper.cpp \
    $$PWD/qvxymodelmapper.cpp \
    $$PWD/qhxymodelmapper.cpp

PRIVATE_HEADERS += \
    $$PWD/xychart_p.h \
    $$PWD/qxyseries_p.h \
    $$PWD/qxymodelmapper_p.h

PUBLIC_HEADERS += \
    $$PWD/qxyseries.h \
    $$PWD/qxymodelmapper.h \
    $$PWD/qvxymodelmapper.h \
    $$PWD/qhxymodelmapper.h

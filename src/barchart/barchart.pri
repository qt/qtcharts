include(vertical/vertical.pri)
include(horizontal/horizontal.pri)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/bar.cpp \
    $$PWD/abstractbarchartitem.cpp \
    $$PWD/qabstractbarseries.cpp \  
    $$PWD/qbarset.cpp \
    $$PWD/qbarmodelmapper.cpp \
    $$PWD/qvbarmodelmapper.cpp \
    $$PWD/qhbarmodelmapper.cpp \
 
PRIVATE_HEADERS += \
    $$PWD/bar_p.h \
    $$PWD/qbarset_p.h \
    $$PWD/abstractbarchartitem_p.h \
    $$PWD/qabstractbarseries_p.h \
    $$PWD/qbarmodelmapper_p.h 

PUBLIC_HEADERS += \
    $$PWD/qabstractbarseries.h \
    $$PWD/qbarset.h \
    $$PWD/qbarmodelmapper.h \
    $$PWD/qvbarmodelmapper.h \
    $$PWD/qhbarmodelmapper.h 

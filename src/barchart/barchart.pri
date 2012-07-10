INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/bar.cpp \
    $$PWD/barchartitem.cpp \
    $$PWD/percentbarchartitem.cpp \
    $$PWD/groupedbarchartitem.cpp \
    $$PWD/qabstractbarseries.cpp \  
    $$PWD/qbarset.cpp \
    $$PWD/qpercentbarseries.cpp \
    $$PWD/qstackedbarseries.cpp \
    $$PWD/qbarseries.cpp \
    $$PWD/stackedbarchartitem.cpp \
    $$PWD/qbarmodelmapper.cpp \
    $$PWD/qvbarmodelmapper.cpp \
    $$PWD/qhbarmodelmapper.cpp \
    $$PWD/qhorizontalbarseries.cpp \
    $$PWD/horizontalbarchartitem.cpp
 
PRIVATE_HEADERS += \
    $$PWD/bar_p.h \
    $$PWD/barchartitem_p.h \
    $$PWD/percentbarchartitem_p.h \
    $$PWD/stackedbarchartitem_p.h \
    $$PWD/groupedbarchartitem_p.h \
    $$PWD/qbarset_p.h \
    $$PWD/qabstractbarseries_p.h \
    $$PWD/qstackedbarseries_p.h\
    $$PWD/qpercentbarseries_p.h \
    $$PWD/qbarseries_p.h \
    $$PWD/qbarmodelmapper_p.h \
    $$PWD/qhorizontalbarseries_p.h \
    $$PWD/horizontalbarchartitem_p.h

PUBLIC_HEADERS += \
    $$PWD/qabstractbarseries.h \
    $$PWD/qbarset.h \
    $$PWD/qpercentbarseries.h \      
    $$PWD/qstackedbarseries.h \
    $$PWD/qbarseries.h \
    $$PWD/qbarmodelmapper.h \
    $$PWD/qvbarmodelmapper.h \
    $$PWD/qhbarmodelmapper.h \
    $$PWD/qhorizontalbarseries.h

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/bar.cpp \
    $$PWD/barchartitem.cpp \
    $$PWD/percentbarchartitem.cpp \
    $$PWD/groupedbarchartitem.cpp \
    $$PWD/qbarseries.cpp \  
    $$PWD/qbarset.cpp \
    $$PWD/qpercentbarseries.cpp \
    $$PWD/qstackedbarseries.cpp \
    $$PWD/qgroupedbarseries.cpp \
    $$PWD/stackedbarchartitem.cpp \
    $$PWD/qbarmodelmapper.cpp
 
PRIVATE_HEADERS += \
    $$PWD/bar_p.h \
    $$PWD/barchartitem_p.h \
    $$PWD/percentbarchartitem_p.h \
    $$PWD/stackedbarchartitem_p.h \
    $$PWD/groupedbarchartitem_p.h \
    $$PWD/qbarset_p.h \
    $$PWD/qbarseries_p.h \
    $$PWD/qstackedbarseries_p.h\
    $$PWD/qpercentbarseries_p.h \
    $$PWD/qgroupedbarseries_p.h \

PUBLIC_HEADERS += \
    $$PWD/qbarseries.h \
    $$PWD/qbarset.h \
    $$PWD/qpercentbarseries.h \      
    $$PWD/qstackedbarseries.h \
    $$PWD/qgroupedbarseries.h \
    $$PWD/qbarmodelmapper.h

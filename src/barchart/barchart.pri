INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/bar.cpp \
    $$PWD/barchartmodel.cpp \
    $$PWD/barchartitem.cpp \
    $$PWD/percentbarchartitem.cpp \
    $$PWD/qbarseries.cpp \  
    $$PWD/qbarset.cpp \
    $$PWD/qpercentbarseries.cpp \
    $$PWD/qstackedbarseries.cpp \
    $$PWD/stackedbarchartitem.cpp \
    $$PWD/barvalue.cpp
 
PRIVATE_HEADERS += \
    $$PWD/bar_p.h \
    $$PWD/barchartmodel_p.h \
    $$PWD/barchartitem_p.h \
    $$PWD/percentbarchartitem_p.h \
    $$PWD/stackedbarchartitem_p.h \
    $$PWD/barvalue_p.h

PUBLIC_HEADERS += \
    $$PWD/qbarseries.h \
    $$PWD/qbarset.h \
    $$PWD/qpercentbarseries.h \      
    $$PWD/qstackedbarseries.h 


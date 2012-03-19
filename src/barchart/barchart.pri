INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/bar.cpp \
    $$PWD/barchartmodel.cpp \
    $$PWD/barpresenter.cpp \
    $$PWD/barpresenterbase.cpp \
    $$PWD/percentbarpresenter.cpp \
    $$PWD/qbarseries.cpp \  
    $$PWD/qbarset.cpp \
    $$PWD/qpercentbarseries.cpp \
    $$PWD/qstackedbarseries.cpp \
    $$PWD/stackedbarpresenter.cpp \ 
    $$PWD/barvalue.cpp
 
PRIVATE_HEADERS += \
    $$PWD/bar_p.h \
    $$PWD/barchartmodel_p.h \
    $$PWD/barpresenter_p.h \
    $$PWD/barpresenterbase_p.h \
    $$PWD/percentbarpresenter_p.h \
    $$PWD/stackedbarpresenter_p.h \
    $$PWD/barvalue_p.h

PUBLIC_HEADERS += \
    $$PWD/qbarseries.h \
    $$PWD/qbarset.h \
    $$PWD/qpercentbarseries.h \      
    $$PWD/qstackedbarseries.h 


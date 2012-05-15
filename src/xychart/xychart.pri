INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/xychartitem.cpp \
    $$PWD/qxyseries.cpp \  
    $$PWD/qxymodelmapper.cpp
    
PRIVATE_HEADERS += \
    $$PWD/xychartitem_p.h \
    $$PWD/qxyseries_p.h

    
PUBLIC_HEADERS += \    
    $$PWD/qxyseries.h \
    $$PWD/qxymodelmapper.h

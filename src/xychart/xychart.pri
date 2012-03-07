INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/xychartitem.cpp \
    $$PWD/qxyseries.cpp  
    
PRIVATE_HEADERS += \
    $$PWD/xychartitem_p.h \
    $$PWD/xychartanimationitem_p.h \
    $$PWD/xychartanimator_p.h
    
PUBLIC_HEADERS += \    
    $$PWD/qxyseries.h  
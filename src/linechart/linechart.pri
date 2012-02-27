INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/linechartanimationitem.cpp \
    $$PWD/linechartitem.cpp \
    $$PWD/qlineseries.cpp 
    
PRIVATE_HEADERS += \
    $$PWD/linechartitem_p.h \
    $$PWD/linechartanimationitem_p.h
    
PUBLIC_HEADERS += \    
    $$PWD/qlineseries.h  
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qlegend.cpp \
    $$PWD/legendmarker.cpp \
    $$PWD/legendlayout.cpp
    
PRIVATE_HEADERS += \
    $$PWD/legendmarker_p.h \
    $$PWD/legendscroller_p.h \
    $$PWD/qlegend_p.h  \
    $$PWD/legendlayout_p.h
   
    
PUBLIC_HEADERS += \
    $$PWD/qlegend.h 
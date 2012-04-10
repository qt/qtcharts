INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qlegend.cpp \
    $$PWD/legendmarker.cpp 
    
PRIVATE_HEADERS += \
    $$PWD/legendmarker_p.h \
    $$PWD/legendscroller_p.h \
    $$PWD/qlegend_p.h 
   
    
PUBLIC_HEADERS += \
    $$PWD/qlegend.h 
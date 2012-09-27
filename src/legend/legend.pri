INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qlegend.cpp \
    $$PWD/legendmarker.cpp \
    $$PWD/legendlayout.cpp \
    $$PWD/qlegendmarker.cpp \
    $$PWD/qpielegendmarker.cpp \
    $$PWD/legendmarkeritem.cpp \
    $$PWD/qbarlegendmarker.cpp \
    $$PWD/qxylegendmarker.cpp
    
PRIVATE_HEADERS += \
    $$PWD/legendmarker_p.h \
    $$PWD/legendscroller_p.h \
    $$PWD/qlegend_p.h  \
    $$PWD/legendlayout_p.h \
    $$PWD/qlegendmarker_p.h \
    $$PWD/legendmarkeritem_p.h \
    $$PWD/qpielegendmarker_p.h \
    $$PWD/qbarlegendmarker_p.h \
    $$PWD/qxylegendmarker_p.h
   
    
PUBLIC_HEADERS += \
    $$PWD/qlegend.h \
    $$PWD/qlegendmarker.h \
    $$PWD/qpielegendmarker.h \
    $$PWD/qbarlegendmarker.h \
    $$PWD/qxylegendmarker.h

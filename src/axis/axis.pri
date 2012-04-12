INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/qaxis.cpp \
    $$PWD/qchartaxiscategories.cpp 
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/qaxis_p.h \
    $$PWD/qchartaxiscategories_p.h

PUBLIC_HEADERS += \    
    $$PWD/qaxis.h \
    $$PWD/qchartaxiscategories.h   
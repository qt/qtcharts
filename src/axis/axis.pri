INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/qaxis.cpp \
    $$PWD/qaxiscategories.cpp 
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/qaxis_p.h \
    $$PWD/qaxiscategories_p.h

PUBLIC_HEADERS += \    
    $$PWD/qaxis.h \
    $$PWD/qaxiscategories.h   
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/chartaxisx.cpp \
    $$PWD/chartaxisy.cpp \
    $$PWD/qaxis.cpp \
    $$PWD/qaxiscategories.cpp 
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/chartaxisx_p.h \
    $$PWD/chartaxisy_p.h \
    $$PWD/qaxis_p.h \
    $$PWD/qaxiscategories_p.h

PUBLIC_HEADERS += \    
    $$PWD/qaxis.h \
    $$PWD/qaxiscategories.h   
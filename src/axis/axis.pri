INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/chartaxisx.cpp \
    $$PWD/chartaxisy.cpp \
    $$PWD/qaxiscategories.cpp \
    $$PWD/qcategoriesaxis.cpp \
    $$PWD/qvaluesaxis.cpp \
    $$PWD/qabstractaxis.cpp
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/chartaxisx_p.h \
    $$PWD/chartaxisy_p.h \
    $$PWD/qaxiscategories_p.h \
    $$PWD/qcategoriesaxis_p.h \
    $$PWD/qvaluesaxis_p.h \
    $$PWD/qabstractaxis_p.h

PUBLIC_HEADERS += \    
    $$PWD/qaxiscategories.h \
    $$PWD/qcategoriesaxis.h \
    $$PWD/qvaluesaxis.h \
    $$PWD/qabstractaxis.h 
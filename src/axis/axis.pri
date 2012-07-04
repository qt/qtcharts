INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/chartvaluesaxisx.cpp \
    $$PWD/chartvaluesaxisy.cpp \
    $$PWD/chartcategoriesaxisx.cpp \
    $$PWD/chartcategoriesaxisy.cpp \
    $$PWD/qbarcategoriesaxis.cpp \
    $$PWD/qintervalaxis.cpp \
    $$PWD/qvaluesaxis.cpp \
    $$PWD/qabstractaxis.cpp
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/chartvaluesaxisx_p.h \
    $$PWD/chartvaluesaxisy_p.h \
    $$PWD/chartcategoriesaxisx_p.h \
    $$PWD/chartcategoriesaxisy_p.h \
    $$PWD/qbarcategoriesaxis_p.h \
    $$PWD/qintervalaxis_p.h \
    $$PWD/qvaluesaxis_p.h \
    $$PWD/qabstractaxis_p.h

PUBLIC_HEADERS += \
    $$PWD/qbarcategoriesaxis.h \
    $$PWD/qintervalaxis.h \
    $$PWD/qvaluesaxis.h \
    $$PWD/qabstractaxis.h 

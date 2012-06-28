INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
#    $$PWD/chartaxisx.cpp \
#    $$PWD/chartaxisy.cpp \
    $$PWD/chartvaluesaxisx.cpp \
    $$PWD/chartvaluesaxisy.cpp \
    $$PWD/chartcategoriesaxisx.cpp \
    $$PWD/chartcategoriesaxisy.cpp \
    $$PWD/qcategoriesaxis.cpp \
    $$PWD/qvaluesaxis.cpp \
    $$PWD/qabstractaxis.cpp
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
#    $$PWD/chartaxisx_p.h \
#    $$PWD/chartaxisy_p.h \
    $$PWD/chartvaluesaxisx_p.h \
    $$PWD/chartvaluesaxisy_p.h \
    $$PWD/chartcategoriesaxisx_p.h \
    $$PWD/chartcategoriesaxisy_p.h \
    $$PWD/qcategoriesaxis_p.h \
    $$PWD/qvaluesaxis_p.h \
    $$PWD/qabstractaxis_p.h

PUBLIC_HEADERS += \
    $$PWD/qcategoriesaxis.h \
    $$PWD/qvaluesaxis.h \
    $$PWD/qabstractaxis.h 

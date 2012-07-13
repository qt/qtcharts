include(valuesaxis/valuesaxis.pri)
include(categoriesaxis/categoriesaxis.pri)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/qabstractaxis.cpp
    
PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/qabstractaxis_p.h

PUBLIC_HEADERS += \
    $$PWD/qabstractaxis.h 

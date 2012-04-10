INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/axis.cpp \
    $$PWD/qchartaxis.cpp \
    $$PWD/qchartaxiscategories.cpp 
    
PRIVATE_HEADERS += \
    $$PWD/axis_p.h \
    $$PWD/qchartaxis_p.h \
    $$PWD/qchartaxiscategories_p.h

PUBLIC_HEADERS += \    
    $$PWD/qchartaxis.h \
    $$PWD/qchartaxiscategories.h   
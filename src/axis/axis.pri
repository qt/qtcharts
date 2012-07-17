#Subdirectiores are defined here, because qt creator doesn't handle nested include(foo.pri) chains very well.

INCLUDEPATH += $$PWD \
    $$PWD/valuesaxis \
    $$PWD/categoriesaxis \
    $$PWD/intervalsaxis

DEPENDPATH += $$PWD \
    $$PWD/valuesaxis \
    $$PWD/categoriesaxis \
    $$PWD/intervalsaxis

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/qabstractaxis.cpp \
    $$PWD/valueaxis/chartvaluesaxisx.cpp \
    $$PWD/valueaxis/chartvaluesaxisy.cpp \
    $$PWD/valueaxis/qvaluesaxis.cpp \
    $$PWD/categoriesaxis/chartcategoriesaxisx.cpp \
    $$PWD/categoriesaxis/chartcategoriesaxisy.cpp \
    $$PWD/categoriesaxis/qbarcategoriesaxis.cpp \
    $$PWD/intervalsaxis/chartintervalsaxisx.cpp \
    $$PWD/intervalsaxis/chartintervalsaxisy.cpp \
    $$PWD/intervalsaxis/qintervalsaxis.cpp

PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/qabstractaxis_p.h \
    $$PWD/valueaxis/chartvaluesaxisx_p.h \
    $$PWD/valueaxis/chartvaluesaxisy_p.h \
    $$PWD/valueaxis/qvaluesaxis_p.h \
    $$PWD/categoriesaxis/chartcategoriesaxisx_p.h \
    $$PWD/categoriesaxis/chartcategoriesaxisy_p.h \
    $$PWD/categoriesaxis/qbarcategoriesaxis_p.h \
    $$PWD/intervalsaxis/chartintervalsaxisx_p.h \
    $$PWD/intervalsaxis/chartintervalsaxisy_p.h \
    $$PWD/intervalsaxis/qintervalsaxis_p.h

PUBLIC_HEADERS += \
    $$PWD/qabstractaxis.h \
    $$PWD/valueaxis/qvaluesaxis.h \
    $$PWD/categoriesaxis/qbarcategoriesaxis.h \
    $$PWD/intervalsaxis/qintervalsaxis.h

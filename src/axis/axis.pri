#Subdirectiores are defined here, because qt creator doesn't handle nested include(foo.pri) chains very well.

INCLUDEPATH += $$PWD \
    $$PWD/valuesaxis \
    $$PWD/categoriesaxis \
    $$PWD/intervalsaxis \
    $$PWD/datetimeaxis

DEPENDPATH += $$PWD \
    $$PWD/valuesaxis \
    $$PWD/categoriesaxis \
    $$PWD/intervalsaxis \
    $$PWD/datetimeaxis

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/qabstractaxis.cpp \
    $$PWD/valuesaxis/chartvaluesaxisx.cpp \
    $$PWD/valuesaxis/chartvaluesaxisy.cpp \
    $$PWD/valuesaxis/qvaluesaxis.cpp \
    $$PWD/categoriesaxis/chartcategoriesaxisx.cpp \
    $$PWD/categoriesaxis/chartcategoriesaxisy.cpp \
    $$PWD/categoriesaxis/qbarcategoriesaxis.cpp \
    $$PWD/intervalsaxis/chartintervalsaxisx.cpp \
    $$PWD/intervalsaxis/chartintervalsaxisy.cpp \
    $$PWD/intervalsaxis/qintervalsaxis.cpp \
    $$PWD/datetimeaxis/chartdatetimeaxisx.cpp \
    $$PWD/datetimeaxis/chartdatetimeaxisy.cpp \
    $$PWD/datetimeaxis/qdatetimeaxis.cpp

PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/qabstractaxis_p.h \
    $$PWD/valuesaxis/chartvaluesaxisx_p.h \
    $$PWD/valuesaxis/chartvaluesaxisy_p.h \
    $$PWD/valuesaxis/qvaluesaxis_p.h \
    $$PWD/categoriesaxis/chartcategoriesaxisx_p.h \
    $$PWD/categoriesaxis/chartcategoriesaxisy_p.h \
    $$PWD/categoriesaxis/qbarcategoriesaxis_p.h \
    $$PWD/intervalsaxis/chartintervalsaxisx_p.h \
    $$PWD/intervalsaxis/chartintervalsaxisy_p.h \
    $$PWD/intervalsaxis/qintervalsaxis_p.h \
    $$PWD/datetimeaxis/chartdatetimeaxisx_p.h \
    $$PWD/datetimeaxis/chartdatetimeaxisy_p.h \
    $$PWD/datetimeaxis/qdatetimeaxis_p.h

PUBLIC_HEADERS += \
    $$PWD/qabstractaxis.h \
    $$PWD/valuesaxis/qvaluesaxis.h \
    $$PWD/categoriesaxis/qbarcategoriesaxis.h \
    $$PWD/intervalsaxis/qintervalsaxis.h \
    $$PWD/datetimeaxis/qdatetimeaxis.h

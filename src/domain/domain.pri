#Subdirectiores are defined here, because qt creator doesn't handle nested include(foo.pri) chains very well.

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/abstractdomain.cpp \
    $$PWD/xydomain.cpp \
    $$PWD/xlogydomain.cpp \
    $$PWD/logxydomain.cpp \
    $$PWD/logxlogydomain.cpp

PRIVATE_HEADERS += \
    $$PWD/abstractdomain_p.h \
    $$PWD/xydomain_p.h \
    $$PWD/xlogydomain_p.h \
    $$PWD/logxydomain_p.h \
    $$PWD/logxlogydomain_p.h

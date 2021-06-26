QT += charts widgets

SOURCES += \
    main.cpp \
    utilities.cpp

HEADERS += \
    utilities.h

target.path = $$[QT_INSTALL_EXAMPLES]/charts/selectedbar
INSTALLS += target

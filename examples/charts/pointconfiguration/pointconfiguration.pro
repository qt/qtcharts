QT += charts \
      widgets

SOURCES += \
    chartwindow.cpp
    main.cpp

HEADERS += \
    chartwindow.h

target.path = $$[QT_INSTALL_EXAMPLES]/charts/pointconfiguration
INSTALLS += target

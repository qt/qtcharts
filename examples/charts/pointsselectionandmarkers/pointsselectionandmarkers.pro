QT += charts \
      widgets

SOURCES += \
    main.cpp \
    utilities.cpp

HEADERS += \
    utilities.h

RESOURCES += \
    pointsselectionandmarkers.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/charts/pointsselectionandmarkers
INSTALLS += target

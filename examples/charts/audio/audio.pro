QT += charts multimedia

HEADERS += \
    widget.h \
    xyseriesiodevice.h

SOURCES += \
    main.cpp\
    widget.cpp \
    xyseriesiodevice.cpp

darwin{
    QMAKE_INFO_PLIST = apple/Info.qmake.plist
}

target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
INSTALLS += target

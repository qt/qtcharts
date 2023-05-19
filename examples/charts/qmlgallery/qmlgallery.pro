QT += charts qml quick

SOURCES += main.cpp

RESOURCES += qmlgallery.qrc

DISTFILES += \
    qml/* \
    qml/customlegend/* \
    qml/f1legends/*

target.path = $$[QT_INSTALL_EXAMPLES]/charts/qmlgallery
INSTALLS += target

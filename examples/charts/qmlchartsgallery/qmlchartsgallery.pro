QT += charts qml quick

SOURCES += main.cpp

RESOURCES += qmlchartsgallery.qrc

DISTFILES += \
    qml/* \
    qml/customlegend/* \
    qml/f1legends/*

target.path = $$[QT_INSTALL_EXAMPLES]/charts/qmlchartsgallery
INSTALLS += target

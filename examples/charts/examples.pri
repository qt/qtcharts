
INCLUDEPATH += ../../../include

LIBS += -L$$OUT_PWD/../../../lib

TEMPLATE = app

QT += charts
QT += core gui widgets

contains(TARGET, qml.*) {
    QT += qml quick
}

target.path = $$[QT_INSTALL_EXAMPLES]/charts/$$TARGET
INSTALLS += target


greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick1
} else {
    QT += declarative
}

SOURCES += $$PWD/qmlapplicationviewer.cpp
HEADERS += $$PWD/qmlapplicationviewer.h
INCLUDEPATH += $$PWD

# Include JS debugger library if QMLJSDEBUGGER_PATH is set
!isEmpty(QMLJSDEBUGGER_PATH) {
    include($$QMLJSDEBUGGER_PATH/qmljsdebugger-lib.pri)
} else {
    DEFINES -= QMLJSDEBUGGER
}


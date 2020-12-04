include( ../tests.pri )

CONFIG += testcase
QT += testlib widgets

!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")

INCLUDEPATH += ../inc
HEADERS += ../inc/tst_definitions.h

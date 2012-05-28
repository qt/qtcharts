!include( ../auto.pri ):error( "Couldn't find the auto.pri file!" )

HEADERS += ../qxyseries/tst_qxyseries.h
SOURCES += tst_qscatterseries.cpp ../qxyseries/tst_qxyseries.cpp

!system_build:mac:QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_AUTOTESTS_BIN_DIR"

#-------------------------------------------------
#
# Project created by QtCreator 2012-02-14T15:27:32
#
#-------------------------------------------------

!include( ../../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
!include( ../../integrated.pri ) {
    error( "Couldn't find the integrated.pri file !")
}

QT       += core gui sql

TARGET = gdpbarchart
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

COPY_DATABASE_COMMAND = $$QMAKE_COPY gdpData $$CHART_BUILD_BIN_DIR/gdpData

win32 {
    COPY_DATABASE_COMMAND = $$replace(COPY_DATABASE_COMMAND, "/","\\")
}

QMAKE_POST_LINK = $$COPY_DATABASE_COMMAND

!include( ../../common.pri ) {
 error( "Couldn't find the common.pri file!" )
}

!include( ../../integrated.pri ) {
 error( "Couldn't find the integrated.pri file !")
}

TARGET = zoomLineChart
TEMPLATE = app
QT += core gui
HEADERS += chartwidget.h
SOURCES += main.cpp chartwidget.cpp





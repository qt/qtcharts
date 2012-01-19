!include( ../../common.pri ) {
 error( Couldn't find the common.pri file! )
}

!include( ../../internal.pri ) {
 error( Couldn't find the internal.pri file !)
}

TARGET = lineChart
TEMPLATE = app
QT += core gui
SOURCES += main.cpp




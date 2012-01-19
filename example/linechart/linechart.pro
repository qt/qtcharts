CONFIG += internal_build

TARGET = lineChart
TEMPLATE = app
QT += core gui
SOURCES += main.cpp

!include( ../../common.pri ) {
 message('missing common pri')
 CONFIG += qtcommercialchart
}



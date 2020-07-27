!include( ../auto.pri ) {
    error( "Couldn't find the auto.pri file!" )
}
SOURCES += tst_qml.cpp
QT += qml quick

!include( ../auto.pri ) {
    error( "Couldn't find the auto.pri file!" )
}
SOURCES += tst_qml.cpp
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick1
} else {
    QT += declarative
}

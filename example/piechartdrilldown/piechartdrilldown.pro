!include( ../example.pri ) {
 error( "Couldn't find the example.pri file!" )
}
TARGET = piechartdrilldown
SOURCES += main.cpp
HEADERS +=


MOC_DIR = $$PWD/moc

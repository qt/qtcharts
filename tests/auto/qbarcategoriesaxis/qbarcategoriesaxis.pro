!include( ../auto.pri ) {
    error( "Couldn't find the auto.pri file!" )
}
HEADERS += ../qabstractaxis/tst_qabstractaxis.h
SOURCES += tst_qbarcategoriesaxis.cpp ../qabstractaxis/tst_qabstractaxis.cpp

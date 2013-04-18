TARGET = qtcommercialchartqml
QT += declarative
IMPORT_INSTALL_PATH = $$[QT_INSTALL_IMPORTS]

!include(../declarative/declarative.pri) {
    error( "Couldn't find the declarative.pri file!" )
}


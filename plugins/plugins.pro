!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \ 
        declarative \
        designer
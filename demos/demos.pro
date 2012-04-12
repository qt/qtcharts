!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

!include( ../build.pri ) {
 error( "Couldn't find the build.pri file !")
}

TEMPLATE = subdirs
SUBDIRS += chartthemes \
           piechartcustomization \
           qmlchart \
           dynamicspline

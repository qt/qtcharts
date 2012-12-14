CURRENTLY_BUILDING_COMPONENTS = "demos"
!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += piechartcustomization \
           dynamicspline \
           nesteddonuts \
           qmlchart \
           qmlweather \
           qmlf1legends \
           qmlcustomizations \
           qmlcustommodel \
           chartinteractions \
           qmlaxes \
           qmlcustomlegend \
           callout

contains(QT_CONFIG, opengl) {
        SUBDIRS +=  chartthemes \
                    qmloscilloscope
} else {
    message("OpenGL not available. Some demos are disabled")
}

contains(QT_CONFIG, multimedia) {
        SUBDIRS += audio
} else {
    message("QtMultimedia library not available. Some demos are disabled")
}

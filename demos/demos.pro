CURRENTLY_BUILDING_COMPONENTS = "demos"
!include( ../config.pri ) {
    error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += piechartcustomization \
           dynamicspline \
           nesteddonuts \
           chartinteractions \
           callout \
           chartthemes

!contains(QT_VERSION, ^5\\..*\\..*$)|qtHaveModule(declarative) {
    SUBDIRS += qmlchart \
           qmlweather \
           qmlf1legends \
           qmlcustomizations \
           qmlaxes \
           qmlcustomlegend \
           qmlpolarchart \
           qmloscilloscope
}

contains(QT_CONFIG, multimedia) {
        SUBDIRS += audio
} else {
    message("QtMultimedia library not available. Some demos are disabled")
}

contains(QT_VERSION, ^5\\..*\\..*$):qtHaveModule(quick) {
    SUBDIRS += quick2chart \
    quick2oscilloscope
}

!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += \ 
    auto \    
    qmlchartproperties \
    qmlchartaxis \
    presenterchart \
    polarcharttest

contains(QT_CONFIG, opengl) {
    SUBDIRS +=  chartwidgettest \
                wavechart \
                chartviewer
} else {
    message("OpenGL not available. Some test apps are disabled")
}

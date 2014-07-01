TEMPLATE = subdirs
SUBDIRS += \ 
    auto \    
    presenterchart \
    polarcharttest \
    boxplottester

contains(QT_CONFIG, opengl) {
    SUBDIRS +=  chartwidgettest \
                wavechart \
                chartviewer
} else {
    message("OpenGL not available. Some test apps are disabled")
}

qtHaveModule(quick) {
    SUBDIRS += qmlchartproperties \
               qmlchartaxis
}

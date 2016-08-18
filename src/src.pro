TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += charts
qtHaveModule(quick):contains(QT_CONFIG, opengl) {
    SUBDIRS += chartsqml2
}

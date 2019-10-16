requires(qtHaveModule(widgets))

qtHaveModule(widgets) {
    QT_FOR_CONFIG += widgets
    requires(qtConfig(graphicsview))
    requires(qtConfig(texthtmlparser))
}

load(qt_parts)

OTHER_FILES += README dist/*

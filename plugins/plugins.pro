!include( ../config.pri ) {
 error( "Couldn't find the config.pri file!" )
}

TEMPLATE = subdirs

contains(QT_VERSION, ^4\\.[0-7]\\.[0-2]\\s*$) | contains(QT_VERSION, ^4\\.[0-6]\\..*) {
    warning("QtCommercial.Charts QML API requires at least Qt 4.7.3. You are using $${QT_VERSION} so the QML API is disabled.")
} else {
    SUBDIRS += declarative
}

!linux-arm*: {
    SUBDIRS += \
            designer
}

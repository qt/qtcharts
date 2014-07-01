!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

RESOURCES += resources.qrc
SOURCES += main.cpp

OTHER_FILES += \
    qml/qmlboxplot/main.qml

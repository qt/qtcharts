!include( ../demos.pri ):error( "Couldn't find the demos.pri file!" )
TARGET = chartthemes
SOURCES = main.cpp themewidget.cpp
HEADERS = themewidget.h

# This is a hack to make binaries to use the internal version of the QtCommercial Charts library on OSX
#CHARTS_LIB_NAME = "lib"$$LIBRARY_NAME".1.dylib"
#CONFIG(debug, debug|release) {
#    CHARTS_LIB_NAME = "lib"$$LIBRARY_NAME".1.dylib"
#}

!system:mac: QMAKE_POST_LINK += "$$MAC_POST_LINK_PREFIX $$MAC_DEMOS_BIN_DIR"

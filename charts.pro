!include(common.pri) {
    error('missing common.pri')
}

TEMPLATE = subdirs
SUBDIRS += src qmlplugin example test
CONFIG += ordered
QMAKE_CXXFLAGS += -g -Wall
unix:QMAKE_DISTCLEAN += -r build bin 
win32:QMAKE_DISTCLEAN += /Q build bin 

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/qtcommercialchart.prf
INSTALLS += feature

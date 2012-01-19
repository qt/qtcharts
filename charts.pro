TEMPLATE = subdirs
SUBDIRS +=  src example #qmlplugin
CONFIG += ordered
QMAKE_CXXFLAGS += -g -Wall
QMAKE_DISTCLEAN += -r build bin 

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/qtcommercialchart.prf
INSTALLS += feature

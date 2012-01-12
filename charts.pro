TEMPLATE = subdirs
SUBDIRS += src #qmlplugin

QMAKE_CXXFLAGS += -g -Wall
QMAKE_DISTCLEAN += -r build

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/charts.prf
INSTALLS += feature


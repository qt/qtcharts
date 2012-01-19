!include(common.pri) {
 error('missing common.pri')
}

TEMPLATE = subdirs
SUBDIRS +=  src example test
CONFIG += ordered
QMAKE_CXXFLAGS += -g -Wall
QMAKE_DISTCLEAN += -r build bin 

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/qtcommercialchart.prf
INSTALLS += feature

!include(common.pri) {
    error('missing common.pri')
}

TEMPLATE = subdirs
SUBDIRS += src examples demos test qmlplugin

integrated_build:{
    message('Configured for integrated build against local libs...')
} else {
    message('Running build aginst system libs...')
    message('Please build example test and qmlplugin after installing library.')
}

CONFIG += ordered
QMAKE_CXXFLAGS += -g -Wall
unix:QMAKE_DISTCLEAN += -r build bin include lib doc/html 
win32:QMAKE_DISTCLEAN += /Q /s build bin include lib doc\\html

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/qtcommercialchart.prf
INSTALLS += feature

doc.target = doc
win32:{
    doc.commands = qdoc3 $$CHART_BUILD_DOC_DIR\\qcharts.qdocconf
}else{
    doc.commands = qdoc3 $$CHART_BUILD_DOC_DIR/qcharts.qdocconf
}

doc.depends = FORCE
QMAKE_EXTRA_TARGETS += docs


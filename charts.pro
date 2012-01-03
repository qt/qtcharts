TEMPLATE = subdirs
SUBDIRS += widget qmlplugin

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/charts.prf
INSTALLS += feature

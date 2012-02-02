CONFIG+=integrated_build #remove if you want to build against installed libs

CHART_BUILD_HEADER_DIR = $$PWD/include
CHART_BUILD_LIB_DIR = $$PWD/lib
CHART_BUILD_DIR = $$PWD/build
CHART_BUILD_BIN_DIR = $$PWD/bin

# hack to fix windows builds
win32:{
    CHART_BUILD_HEADER_DIR = $$replace(CHART_BUILD_HEADER_DIR, "/","\\")
    CHART_BUILD_LIB_DIR = $$replace(CHART_BUILD_LIB_DIR, "/","\\")
    CHART_BUILD_BUILD_DIR = $$replace(CHART_BUILD_BUILD_DIR, "/","\\")
    CHART_BUILD_BIN_DIR = $$replace(CHART_BUILD_BIN_DIR, "/","\\")
}

mac: {
    # TODO: The following qmake flags are a work-around to make QtCommercial Charts compile on
    # QtCommercial 4.8. On the other hand Charts builds successfully with Qt open source 4.8
    # without these definitions, so this is probably a configuration issue on QtCommercial 4.8;
    # it should probably define the minimum OSX version to be 10.5...
    QMAKE_CXXFLAGS *= -mmacosx-version-min=10.5
    QMAKE_LFLAGS *= -mmacosx-version-min=10.5
}

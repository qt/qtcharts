
#check if shadow build
!contains($${PWD}, $${OUT_PWD}){
    search = "$$PWD:::"
    temp = $$split(search,"/")    
    temp = $$last(temp)
    path = $$replace(search,$$temp,'')
    temp = $$split(OUT_PWD,$$path)
    temp = $$split(temp,'/')
    temp = $$first(temp)
    path = "$${path}$${temp}"
    SHADOW=$$path   
}else{
    SHADOW=$$PWD
    CONFIG-=development_build 
}

CHART_BUILD_PUBLIC_HEADER_DIR = $$SHADOW/include
CHART_BUILD_PRIVATE_HEADER_DIR = $$CHART_BUILD_PUBLIC_HEADER_DIR/private
CHART_BUILD_LIB_DIR = $$SHADOW/lib
CHART_BUILD_DIR = $$SHADOW/build
CHART_BUILD_BIN_DIR = $$SHADOW/bin
CHART_BUILD_PLUGIN_DIR = $$CHART_BUILD_LIB_DIR/QtCommercial/Chart
CHART_BUILD_DOC_DIR = $$SHADOW/doc


# hack to fix windows builds
win32:{
    CHART_BUILD_PUBLIC_HEADER_DIR = $$replace(CHART_BUILD_PUBLIC_HEADER_DIR, "/","\\")
    CHART_BUILD_PRIVATE_HEADER_DIR = $$replace(CHART_BUILD_PRIVATE_HEADER_DIR, "/","\\")
    CHART_BUILD_LIB_DIR = $$replace(CHART_BUILD_LIB_DIR, "/","\\")
    CHART_BUILD_BUILD_DIR = $$replace(CHART_BUILD_BUILD_DIR, "/","\\")
    CHART_BUILD_BIN_DIR = $$replace(CHART_BUILD_BIN_DIR, "/","\\")
    CHART_BUILD_PLUGIN_DIR = $$replace(CHART_BUILD_PLUGIN_DIR, "/","\\")
    CHART_BUILD_DOC_DIR = $$replace(CHART_BUILD_DOC_DIR, "/","\\")
}

mac: {
    # TODO: The following qmake flags are a work-around to make QtCommercial Charts compile on
    # QtCommercial 4.8. On the other hand Charts builds successfully with Qt open source 4.8
    # without these definitions, so this is probably a configuration issue on QtCommercial 4.8;
    # it should probably define the minimum OSX version to be 10.5...
    QMAKE_CXXFLAGS *= -mmacosx-version-min=10.5
    QMAKE_LFLAGS *= -mmacosx-version-min=10.5
}

development_build: {
    DEFINES+=DEVELOPMENT_BUILD
    CONFIG+=local_build
}
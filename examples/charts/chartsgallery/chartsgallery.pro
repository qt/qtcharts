QT += charts

HEADERS += \
    areawidget.h \
    barmodelmappermodel.h \
    barmodelmapperwidget.h \
    boxplotdatareader.h \
    boxplotwidget.h \
    barwidget.h \
    barpercentwidget.h \
    barstackedwidget.h \
    callout.h \
    calloutwidget.h \
    calloutview.h \
    candlestickwidget.h \
    candlestickdatareader.h \
    contentwidget.h \
    customchartwidget.h \
    datetimeaxiswidget.h \
    donutbreakdownchart.h \
    donutbreakdownmainslice.h \
    donutbreakdownwidget.h \
    donutwidget.h \
    dynamicsplinewidget.h \
    horizontalbarwidget.h \
    horizontalpercentbarwidget.h \
    horizontalstackedbarwidget.h \
    interactionswidget.h \
    interactionsview.h \
    interactionschart.h \
    legendwidget.h \
    legendmarkerswidget.h \
    lightmarkerswidget.h \
    lineandbarwidget.h \
    linewidget.h \
    logaxiswidget.h \
    modeldatamodel.h \
    modeldatawidget.h \
    multiaxiswidget.h \
    nesteddonutswidget.h \
    mainwidget.h \
    pccpentool.h \
    pccbrushtool.h \
    pcccustomslice.h \
    pccwidget.h \
    piedrilldownchart.h \
    piedrilldownslice.h \
    piedrilldownwidget.h \
    piewidget.h \
    pointconfigurationwidget.h \
    polarchartview.h \
    polarchartwidget.h \
    scatterinteractionswidget.h \
    scatterwidget.h \
    selectedbarwidget.h \
    splinewidget.h \
    stackeddrilldownchart.h \
    stackeddrilldownseries.h \
    stackeddrilldownwidget.h \
    temperaturerecordswidget.h \
    themewidget.h

SOURCES += \
    areawidget.cpp \
    barmodelmappermodel.cpp \
    barmodelmapperwidget.cpp \
    boxplotdatareader.cpp \
    boxplotwidget.cpp \
    barwidget.cpp \
    barpercentwidget.cpp \
    barstackedwidget.cpp \
    callout.cpp \
    calloutwidget.cpp \
    calloutview.cpp \
    candlestickwidget.cpp \
    candlestickdatareader.cpp \
    contentwidget.cpp \
    customchartwidget.cpp \
    datetimeaxiswidget.cpp \
    donutbreakdownchart.cpp \
    donutbreakdownmainslice.cpp \
    donutbreakdownwidget.cpp \
    donutwidget.cpp \
    dynamicsplinewidget.cpp \
    horizontalbarwidget.cpp \
    horizontalpercentbarwidget.cpp \
    horizontalstackedbarwidget.cpp \
    interactionswidget.cpp \
    interactionsview.cpp \
    interactionschart.cpp \
    legendwidget.cpp \
    legendmarkerswidget.cpp \
    lightmarkerswidget.cpp \
    lineandbarwidget.cpp \
    linewidget.cpp \
    logaxiswidget.cpp \
    main.cpp \
    modeldatamodel.cpp \
    modeldatawidget.cpp \
    multiaxiswidget.cpp \
    nesteddonutswidget.cpp \
    mainwidget.cpp \
    pccpentool.cpp \
    pccbrushtool.cpp \
    pcccustomslice.cpp \
    pccwidget.cpp \
    piedrilldownchart.cpp \
    piedrilldownslice.cpp \
    piedrilldownwidget.cpp \
    piewidget.cpp \
    pointconfigurationwidget.cpp \
    polarchartview.cpp \
    polarchartwidget.cpp \
    scatterinteractionswidget.cpp \
    scatterwidget.cpp \
    selectedbarwidget.cpp \
    splinewidget.cpp \
    stackeddrilldownchart.cpp \
    stackeddrilldownseries.cpp \
    stackeddrilldownwidget.cpp \
    temperaturerecordswidget.cpp \
    themewidget.cpp

RESOURCES += chartsgallery.qrc

FORMS += themewidget.ui

target.path = $$[QT_INSTALL_EXAMPLES]/charts/chartsgallery
INSTALLS += target

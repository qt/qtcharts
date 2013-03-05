/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qchartsplugin.h"
#include "qchartview.h"
#include <QtPlugin>

QTCOMMERCIALCHART_USE_NAMESPACE

QChartsPlugin::QChartsPlugin(QObject *parent) :
    QObject(parent)
{
    // TODO Auto-generated constructor stub
}

QChartsPlugin::~QChartsPlugin()
{
    // TODO Auto-generated destructor stub
}

QString QChartsPlugin::name() const
{
    return "QChartView";
}

QString QChartsPlugin::includeFile() const
{
#ifdef linux
    QString myNewLine = "\n";
#endif
#ifdef WIN32
    QString myNewLine = "\n\r";
#endif
#ifdef __APPLE__
    QString myNewLine = "\n";
#endif
    return "<qchartview.h>" + myNewLine + "#include <chartsnamespace.h>";
}

QString QChartsPlugin::group() const
{
    return tr("QCharts Widgets");
}

QIcon QChartsPlugin::icon() const
{
    return QIcon(":/images/qcharts.png");
}

QString QChartsPlugin::toolTip() const
{
    return tr("An qcharts view widget");
}

QString QChartsPlugin::whatsThis() const
{
    return tr("This widget is presents QChartView widget");
}

bool QChartsPlugin::isContainer() const
{
    return false;
}

QWidget *QChartsPlugin::createWidget(QWidget *parent)
{
    return new QChartView(new QChart(), parent);
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    Q_EXPORT_PLUGIN2(qtcommercialchart, QChartsPlugin)
#endif


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
    return "QCharts";
}

QString QChartsPlugin::includeFile() const
{
    return "<qchartview.h>";
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
    return tr("An qcharts widget");
}

QString QChartsPlugin::whatsThis() const
{
    return tr("This widget is presents QCharts view widget");
}

bool QChartsPlugin::isContainer() const
{
    return false;
}

QWidget* QChartsPlugin::createWidget(QWidget *parent)
{
    return new QChartView(new QChart(), parent);
}

Q_EXPORT_PLUGIN2(qtcommercialchart, QChartsPlugin)

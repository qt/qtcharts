/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "qchartsplugin.h"
#include <QtCharts/QChartView>
#include <QtCore/QtPlugin>

QT_USE_NAMESPACE

QChartsPlugin::QChartsPlugin(QObject *parent) :
    QObject(parent)
{
}

QChartsPlugin::~QChartsPlugin()
{
}

QString QChartsPlugin::name() const
{
    return QStringLiteral("QChartView");
}

QString QChartsPlugin::includeFile() const
{
    return QStringLiteral("<QtCharts/QChartView>");
}

QString QChartsPlugin::group() const
{
    return tr("Qt Charts Widgets");
}

QIcon QChartsPlugin::icon() const
{
    return QIcon(QStringLiteral(":/images/qcharts.png"));
}

QString QChartsPlugin::toolTip() const
{
    return tr("A Qt Charts view widget");
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

QString QChartsPlugin::domXml() const
{
    return QStringLiteral("\
    <ui language=\"c++\">\
        <widget class=\"QChartView\" name=\"chartview\">\
            <property name=\"geometry\">\
                <rect>\
                    <x>0</x>\
                    <y>0</y>\
                    <width>200</width>\
                    <height>200</height>\
                </rect>\
            </property>\
        </widget>\
    </ui>");
}


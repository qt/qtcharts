// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "drilldownseries.h"

QT_USE_NAMESPACE

DrilldownBarSeries::DrilldownBarSeries(QStringList categories, int maxValue, QObject *parent)
    : QStackedBarSeries(parent),
      m_maxValue(maxValue)
{
    m_categories = categories;
}

void DrilldownBarSeries::mapDrilldownSeries(int index, DrilldownBarSeries *drilldownSeries)
{
    m_DrilldownSeries[index] = drilldownSeries;
}

DrilldownBarSeries *DrilldownBarSeries::drilldownSeries(int index)
{
    return m_DrilldownSeries[index];
}

QStringList DrilldownBarSeries::categories()
{
    return m_categories;
}

int DrilldownBarSeries::maxValue()
{
    return m_maxValue;
}

#include "moc_drilldownseries.cpp"

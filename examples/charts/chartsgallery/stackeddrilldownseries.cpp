// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "stackeddrilldownseries.h"

StackedDrilldownSeries::StackedDrilldownSeries(const QStringList &categories,
                                               int maxValue,
                                               QObject *parent)
    : QStackedBarSeries(parent)
    , m_maxValue(maxValue)
{
    m_categories = categories;
}

void StackedDrilldownSeries::mapDrilldownSeries(int index, StackedDrilldownSeries *drilldownSeries)
{
    m_drilldownSeries[index] = drilldownSeries;
}

StackedDrilldownSeries *StackedDrilldownSeries::drilldownSeries(int index) const
{
    return m_drilldownSeries[index];
}

QStringList StackedDrilldownSeries::categories() const
{
    return m_categories;
}

int StackedDrilldownSeries::maxValue() const
{
    return m_maxValue;
}

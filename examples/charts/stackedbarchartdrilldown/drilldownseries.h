// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef DRILLDOWNSERIES_H
#define DRILLDOWNSERIES_H

#include <QtCharts/QStackedBarSeries>
#include <QtCore/QMap>

QT_USE_NAMESPACE

//! [1]
class DrilldownBarSeries : public QStackedBarSeries
{
    Q_OBJECT
public:
    DrilldownBarSeries(QStringList categories, int maxValue, QObject *parent = 0);

    void mapDrilldownSeries(int index, DrilldownBarSeries *drilldownSeries);

    DrilldownBarSeries *drilldownSeries(int index);

    QStringList categories();

    int maxValue();

private:
    QMap<int, DrilldownBarSeries *> m_DrilldownSeries;
    QStringList m_categories;
    int m_maxValue;
};
//! [1]

#endif // DRILLDOWNSERIES_H

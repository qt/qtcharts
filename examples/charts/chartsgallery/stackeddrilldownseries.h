// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef STACKEDDRILLDOWNSERIES_H
#define STACKEDDRILLDOWNSERIES_H

#include <QMap>
#include <QStackedBarSeries>

//! [1]
class StackedDrilldownSeries : public QStackedBarSeries
{
    Q_OBJECT
public:
    StackedDrilldownSeries(const QStringList &categories, int maxValue, QObject *parent = nullptr);

    void mapDrilldownSeries(int index, StackedDrilldownSeries *drilldownSeries);
    StackedDrilldownSeries *drilldownSeries(int index) const;
    QStringList categories() const;
    int maxValue() const;

private:
    QMap<int, StackedDrilldownSeries *> m_drilldownSeries;
    QStringList m_categories;
    int m_maxValue = 0;
};
//! [1]

#endif

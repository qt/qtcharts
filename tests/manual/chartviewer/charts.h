// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only


#ifndef CHARTS_H
#define CHARTS_H
#include "model.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QSharedPointer>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QChart;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class Chart
{
public:
    virtual ~Chart() {};
    virtual QChart *createChart(const DataTable &table) = 0;
    virtual QString name() = 0;
    virtual QString category() = 0;
    virtual QString subCategory() = 0;

};

namespace Charts
{

    typedef QList<Chart *> ChartList;

    inline ChartList &chartList()
    {
        static ChartList list;
        return list;
    }

    inline bool findChart(Chart *chart)
    {
        ChartList &list = chartList();
        if (list.contains(chart))
            return true;

        foreach (Chart *item, list) {
            if (item->name() == chart->name() && item->category() == chart->category() && item->subCategory() == chart->subCategory())
                return true;
        }
        return false;
    }

    inline void addChart(Chart *chart)
    {
        ChartList &list = chartList();
        if (!findChart(chart))
            list.append(chart);
    }
}

template <class T>
class ChartWrapper
{
public:
    QSharedPointer<T> chart;
    ChartWrapper() : chart(new T) { Charts::addChart(chart.data()); }
};

#define DECLARE_CHART(chartType) static ChartWrapper<chartType> chartType;
#define DECLARE_CHART_TEMPLATE(chartType,chartName) static ChartWrapper<chartType> chartName;

#endif

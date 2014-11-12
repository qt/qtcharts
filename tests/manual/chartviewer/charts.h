/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/


#ifndef CHARTS_H
#define CHARTS_H
#include "model.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QSharedPointer>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

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

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/
#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QAbstractSeries;
class QPieSlice;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~DrilldownChart();
    void changeSeries(QAbstractSeries *series);

public Q_SLOTS:
    void handleSliceClicked(QPieSlice *slice);

private:
    QAbstractSeries *m_currentSeries;
};

#endif // DRILLDOWNCHART_H

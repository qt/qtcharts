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

#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/QChart>
#include "drilldownseries.h"

QT_CHARTS_USE_NAMESPACE

//! [1]
class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    void changeSeries(DrilldownBarSeries *series);

public Q_SLOTS:
    void handleClicked(int index, QBarSet *barset);

private:
    DrilldownBarSeries *m_currentSeries;
};
//! [1]

#endif // DRILLDOWNCHART_H

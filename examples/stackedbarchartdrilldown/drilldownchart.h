/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QChart>
#include "drilldownseries.h"

QTCOMMERCIALCHART_USE_NAMESPACE

//! [2]
class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    void changeSeries(QSeries* series);

public Q_SLOTS:
    void handleClicked(QBarSet *barset, QString category, Qt::MouseButtons button);

private:
    QSeries* m_currentSeries;
};
//! [2]

#endif // DRILLDOWNCHART_H

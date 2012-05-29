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

#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include <qchartglobal.h>
#include <qlineseries.h>
#include <QList>
#include <QPointF>
#include <QtGlobal>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSplineSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QSplineSeries : public QLineSeries
{
    Q_OBJECT

public:
    explicit QSplineSeries(QObject *parent = 0);
    ~QSplineSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QSplineSeries)
    Q_DISABLE_COPY(QSplineSeries)
    friend class SplineChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSPLINESERIES_H

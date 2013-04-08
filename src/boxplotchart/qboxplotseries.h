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

#ifndef QBOXPLOTSERIES_H
#define QBOXPLOTSERIES_H

#include <qchartglobal.h>
#include <qabstractbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBoxPlotSeriesPrivate;
//class QBarSet;

class QTCOMMERCIALCHART_EXPORT QBoxPlotSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QBoxPlotSeries(QObject *parent = 0);
    ~QBoxPlotSeries();

    QAbstractSeries::SeriesType type() const;

    void mika();

    void setBrush(const QBrush &brush);
    QBrush brush() const;
    void setPen(const QPen &pen);
    QPen pen() const;

private:
    Q_DECLARE_PRIVATE(QBoxPlotSeries)
    Q_DISABLE_COPY(QBoxPlotSeries)
    friend class BoxPlotChartItem;
    friend class QBoxPlotLegendMarkerPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBOXPLOTSERIES_H

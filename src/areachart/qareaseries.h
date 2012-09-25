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

#ifndef QAREASERIES_H
#define QAREASERIES_H

#include <qchartglobal.h>
#include <qabstractseries.h>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QLineSeries;
class QAreaSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QAreaSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(QLineSeries *upperSeries READ upperSeries)
    Q_PROPERTY(QLineSeries *lowerSeries READ lowerSeries)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)

public:
    explicit QAreaSeries(QObject *parent = 0);
    explicit QAreaSeries(QLineSeries *upperSeries, QLineSeries *lowerSeries = 0);
    ~QAreaSeries();

public:
    QAbstractSeries::SeriesType type() const;

    void setUpperSeries(QLineSeries *series);
    QLineSeries *upperSeries() const;
    void setLowerSeries(QLineSeries *series);
    QLineSeries *lowerSeries() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setBorderColor(const QColor &color);
    QColor borderColor() const;

    void setPointsVisible(bool visible = true);
    bool pointsVisible() const;

Q_SIGNALS:
    void clicked(const QPointF &point);
    void selected();
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);

private:
    Q_DECLARE_PRIVATE(QAreaSeries)
    Q_DISABLE_COPY(QAreaSeries)
    friend class AreaLegendMarker;
    friend class AreaChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QAREASERIES_H

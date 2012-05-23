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

#ifndef AREACHARTITEM_H
#define AREACHARTITEM_H

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAreaSeries;
class AreaChartItem;

class AreaChartItem : public ChartItem
{
    Q_OBJECT
public:
    AreaChartItem(QAreaSeries *areaSeries, ChartPresenter *presenter);
    ~AreaChartItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    LineChartItem* upperLineItem() const { return m_upper; }
    LineChartItem* lowerLineItem() const { return m_lower; }

    void updatePath();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked(const QPointF &point);

public Q_SLOTS:
    void handleUpdated();
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF &size);

private:
    QAreaSeries* m_series;
    LineChartItem* m_upper;
    LineChartItem* m_lower;
    QPainterPath m_path;
    QRectF m_rect;
    QRectF m_clipRect;
    QPen m_linePen;
    QPen m_pointPen;
    QBrush m_brush;
    bool m_pointsVisible;

};

class AreaBoundItem : public LineChartItem
{
public:
    AreaBoundItem(AreaChartItem *item,QLineSeries *lineSeries) : LineChartItem(lineSeries, 0), m_item(item) {}
    ~AreaBoundItem() {}

    void updateGeometry() {
        LineChartItem::updateGeometry();
        m_item->updatePath();
    }

private:
    AreaChartItem* m_item;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

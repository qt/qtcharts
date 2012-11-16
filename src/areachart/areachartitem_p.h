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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

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
    AreaChartItem(QAreaSeries *areaSeries, QGraphicsItem* item = 0);
    ~AreaChartItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    LineChartItem *upperLineItem() const { return m_upper; }
    LineChartItem *lowerLineItem() const { return m_lower; }

    void updatePath();

    void setPresenter(ChartPresenter *presenter);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

Q_SIGNALS:
    void clicked(const QPointF &point);    
    void hovered(const QPointF &point, bool state);

public Q_SLOTS:
    void handleUpdated();
    void handleDomainUpdated();

private:
    QAreaSeries *m_series;
    LineChartItem *m_upper;
    LineChartItem *m_lower;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    QBrush m_brush;
    bool m_pointsVisible;

};

class AreaBoundItem : public LineChartItem
{
public:
    AreaBoundItem(AreaChartItem *area, QLineSeries *lineSeries,QGraphicsItem* item = 0)
        : LineChartItem(lineSeries, item), m_item(area)
    {
    }
    ~AreaBoundItem() {}

    void updateGeometry()
    {
        LineChartItem::updateGeometry();
        m_item->updatePath();
    }

private:
    AreaChartItem *m_item;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

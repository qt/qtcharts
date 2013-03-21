/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include "qchartglobal.h"
#include "xychart_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLineSeries;
class ChartPresenter;

class LineChartItem :  public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit LineChartItem(QLineSeries *series, QGraphicsItem* item = 0);
    ~LineChartItem() {}

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    QPainterPath path() const { return m_linePath; }

public Q_SLOTS:
    void handleUpdated();

protected:
    void updateGeometry();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void suppressPoints() { m_pointsVisible = false; }

private:
    QLineSeries *m_series;
    QPainterPath m_path;
    QPainterPath m_linePath;
    QVector<QPointF> m_points;
    QRectF m_rect;
    QPen m_linePen;
    bool m_pointsVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

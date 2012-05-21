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

#ifndef PIECHARTITEM_H
#define PIECHARTITEM_H

#include "qpieseries.h"
#include "chartitem_p.h"
#include "piesliceitem_p.h"

class QGraphicsItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSlice;
class ChartPresenter;

class PieChartItem : public ChartItem
{
    Q_OBJECT

public:
    explicit PieChartItem(QPieSeries *series, ChartPresenter *presenter);
    ~PieChartItem();

    // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

public Q_SLOTS:
    // from Chart
    virtual void handleGeometryChanged(const QRectF &rect);
    virtual void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    virtual void rangeXChanged(qreal min, qreal max, int tickXCount);
    virtual void rangeYChanged(qreal min, qreal max, int tickYCount);

    void initialize();
    void updateLayout();
    void handleSlicesAdded(QList<QPieSlice*> slices);
    void handleSlicesRemoved(QList<QPieSlice*> slices);
    void handleSliceChanged();

private:
    PieSliceData updateSliceGeometry(QPieSlice *slice);

private:
    QHash<QPieSlice*, PieSliceItem*> m_sliceItems;
    QPieSeries *m_series;
    QRectF m_rect;
    QPointF m_pieCenter;
    qreal m_pieRadius;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIECHARTITEM_H

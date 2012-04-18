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

typedef QHash<PieSliceItem*, PieSliceData> PieLayout;

class PieChartItem : public ChartItem
{
    Q_OBJECT

public:
    // TODO: use a generic data class instead of x and y
    PieChartItem(QPieSeries *series, ChartPresenter *presenter);
    ~PieChartItem();

public: // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

public Q_SLOTS:
    void initialize();
    void handleSlicesAdded(QList<QPieSlice*> slices);
    void handleSlicesRemoved(QList<QPieSlice*> slices);
    void handlePieLayoutChanged();
    void handleSliceChanged();
    void handleDomainChanged(qreal, qreal, qreal, qreal);
    void handleGeometryChanged(const QRectF& rect);

public:
    void calculatePieLayout();
    PieSliceData sliceData(QPieSlice *slice);
    PieLayout calculateLayout();
    void applyLayout(const PieLayout &layout);
    void updateLayout(PieSliceItem *sliceItem, const PieSliceData &sliceData);
    void setLayout(const PieLayout &layout);
    void setLayout(PieSliceItem *sliceItem, const PieSliceData &sliceData);

private:
    friend class PieSliceItem;
    QHash<QPieSlice*, PieSliceItem*> m_slices;
    QPieSeries *m_series;
    QRectF m_rect;
    QPointF m_pieCenter;
    qreal m_pieRadius;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIECHARTITEM_H

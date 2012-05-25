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

#ifndef BARCHARTITEM_H
#define BARCHARTITEM_H

#include "chartitem_p.h"
#include "qbarseries.h"
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Bar;
class QAxisCategories;
class QChart;

//typedef QVector<QRectF> BarLayout;

class BarChartItem : public ChartItem
{
    Q_OBJECT
public:
    BarChartItem(QBarSeries *series, ChartPresenter *presenter);
    virtual ~BarChartItem();

public:
    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    virtual void dataChanged();     // data of series has changed -> need to recalculate bar sizes

    virtual QVector<QRectF> calculateLayout();
    void applyLayout(const QVector<QRectF> &layout);
    void setLayout(const QVector<QRectF> &layout);
    void updateLayout(const QVector<QRectF> &layout);

    QRectF geometry() const { return m_rect;}

public Q_SLOTS:
    void handleModelChanged();
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF &size);
    void handleLayoutChanged();
    void labelsVisibleChanged(bool visible);

protected:

    qreal m_domainMinX;
    qreal m_domainMaxX;
    qreal m_domainMinY;
    qreal m_domainMaxY;

    QRectF m_rect;
    QVector<QRectF> m_layout;

    // Not owned.
    QBarSeries *m_series;
    QList<Bar *> m_bars;
    QList<QGraphicsSimpleTextItem *> m_labels;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTITEM_H

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


#ifndef ABSTRACTBARCHARTITEM_H
#define ABSTRACTBARCHARTITEM_H

#include "chartitem_p.h"
#include "qabstractbarseries.h"
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Bar;
class QAxisCategories;
class QChart;
class AbstractBarAnimation;

class AbstractBarChartItem : public ChartItem
{
    Q_OBJECT
public:
    AbstractBarChartItem(QAbstractBarSeries *series, ChartPresenter *presenter);
    virtual ~AbstractBarChartItem();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    virtual QVector<QRectF> calculateLayout() = 0;
    virtual void applyLayout(const QVector<QRectF> &layout);
    virtual void setAnimation(AbstractBarAnimation* animation);
    void setLayout(const QVector<QRectF> &layout);
    void updateLayout(const QVector<QRectF> &layout);


    QRectF geometry() const { return m_rect;}

public Q_SLOTS:
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF &size);
    void handleLayoutChanged();
    void handleLabelsVisibleChanged(bool visible);
    void handleDataStructureChanged();     // structure of of series has changed, recreate graphic items
    void handleVisibleChanged();

protected:

    qreal m_domainMinX;
    qreal m_domainMaxX;
    qreal m_domainMinY;
    qreal m_domainMaxY;

    QRectF m_rect;
    QVector<QRectF> m_layout;

    AbstractBarAnimation *m_animation;

    // Not owned.
    QAbstractBarSeries *m_series;
    QList<Bar *> m_bars;
    QList<QGraphicsSimpleTextItem *> m_labels;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // ABSTRACTBARCHARTITEM_H

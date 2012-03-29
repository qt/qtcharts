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

#ifndef XYCHARTITEM_H
#define XYCHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QXYSeries;

class XYChartItem :  public ChartItem
{
     Q_OBJECT
public:
     explicit XYChartItem(QXYSeries *series, ChartPresenter *presenter);
    ~XYChartItem(){};

    QVector<QPointF> points() const {return m_points;}
    QRectF clipRect() const { return m_clipRect;}


public Q_SLOTS:
    void handlePointAdded(int index);
    void handlePointRemoved(int index);
    void handlePointReplaced(int index);
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF &size);

Q_SIGNALS:
    void clicked(const QPointF& point);

protected:

    virtual void setLayout(QVector<QPointF> &points);
    virtual void updateLayout(QVector<QPointF> &oldPoints,QVector<QPointF> &newPoints,int index = 0);

    QPointF calculateGeometryPoint(const QPointF &point) const;
    QPointF calculateGeometryPoint(int index) const;
    QPointF calculateDomainPoint(const QPointF &point) const;
    QVector<QPointF> calculateGeometryPoints() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    inline bool isEmpty();

private:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    QXYSeries* m_series;
    QSizeF m_size;
    QRectF m_clipRect;
    QVector<QPointF> m_points;

    friend class XYAnimation;
    friend class AreaChartItem;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif

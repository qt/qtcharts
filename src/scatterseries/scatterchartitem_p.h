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

#ifndef SCATTERCHARTITEM_H
#define SCATTERCHARTITEM_H

#include "qchartglobal.h"
#include "xychartitem_p.h"
#include <QGraphicsEllipseItem>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QScatterSeries;
class Marker;

class ScatterChartItem : public XYChartItem
{
    Q_OBJECT
public:
    explicit ScatterChartItem(QScatterSeries *series, ChartPresenter *presenter);

public:
    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

    void markerSelected(Marker *item);

public Q_SLOTS:
    void handleUpdated();

private:
    void createPoints(int count);
    void deletePoints(int count);

protected:
    void setLayout(QVector<QPointF> &points);

private:
    QScatterSeries *m_series;
    QGraphicsItemGroup m_items;
    int m_shape;
    int m_size;
    QRectF m_rect;

};


class Marker: public QAbstractGraphicsShapeItem
{

public:

   Marker(QAbstractGraphicsShapeItem *item , ScatterChartItem *parent) : QAbstractGraphicsShapeItem(0) ,m_item(item), m_parent(parent), m_index(-1)
   {
   }

   ~Marker()
   {
       delete m_item;
   }

   void setIndex(int index)
   {
       m_index=index;
   }

   int index() const
   {
       return m_index;
   }

   QPainterPath shape() const
   {
       return m_item->shape();
   }

   QRectF boundingRect() const
   {
       return m_item->boundingRect();
   }

   bool contains(const QPointF &point) const
   {
       return m_item->contains(point);
   }

   void setPen(const QPen &pen)
   {
       m_item->setPen(pen);
   }

   void setBrush(const QBrush &brush)
   {
       m_item->setBrush(brush);
   }

   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
   {
       m_item->paint(painter,option,widget);
   }

protected:

   void mousePressEvent(QGraphicsSceneMouseEvent *event)
   {
       Q_UNUSED(event)
       m_parent->markerSelected(this);
   }

private:
   QAbstractGraphicsShapeItem* m_item;
   ScatterChartItem* m_parent;
   int m_index;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SCATTERPRESENTER_H

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

#include "scatterchartitem_p.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ScatterChartItem::ScatterChartItem(QScatterSeries *series, ChartPresenter *presenter) :
    XYChartItem(series,presenter),
    m_series(series),
    m_items(this),
    m_shape(QScatterSeries::MarkerShapeRectangle),
    m_size(15)

{
    QObject::connect(m_series->d_func(),SIGNAL(updated()), this, SLOT(handleUpdated()));

    setZValue(ChartPresenter::ScatterSeriesZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);

    handleUpdated();

    m_items.setHandlesChildEvents(false);

    // TODO: how to draw a drop shadow?
//    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect();
//    dropShadow->setOffset(2.0);
//    dropShadow->setBlurRadius(2.0);
//    setGraphicsEffect(dropShadow);
}


QRectF ScatterChartItem::boundingRect() const
{
    return m_rect;
}

void ScatterChartItem::createPoints(int count)
{
    for (int i = 0; i < count; ++i) {

        QGraphicsItem *item = 0;

        switch (m_shape) {
                   case QScatterSeries::MarkerShapeCircle:{
                       QGraphicsEllipseItem* i = new QGraphicsEllipseItem(0,0,m_size,m_size);
                       const QRectF& rect = i->boundingRect();
                       i->setPos(-rect.width()/2,-rect.height()/2);
                       item = new Marker(i,this);
                       break;
                   }
                   case QScatterSeries::MarkerShapeRectangle:{
                       QGraphicsRectItem* i = new QGraphicsRectItem(0,0,m_size,m_size);
                       i->setPos(-m_size/2,-m_size/2);
                       item = new Marker(i,this);
                       break;
                   }
                   default:
                       qWarning()<<"Unsupported marker type";
                       break;

        }
        m_items.addToGroup(item);
    }
}

void ScatterChartItem::deletePoints(int count)
{
    QList<QGraphicsItem *> items = m_items.childItems();

    for (int i = 0; i < count; ++i) {
        delete(items.takeLast());
    }
}

void ScatterChartItem::markerSelected(Marker *marker)
{
    emit XYChartItem::clicked(marker->point());
}

void ScatterChartItem::setLayout(QVector<QPointF>& points)
{
    if(points.size()==0)
    {
        XYChartItem::setLayout(points);
        return;
    }

    int diff = m_items.childItems().size() - points.size();

    if(diff>0) {
        deletePoints(diff);
    }
    else if(diff<0) {
        createPoints(-diff);
    }

    if(diff!=0) handleUpdated();

    QList<QGraphicsItem*> items = m_items.childItems();

    for (int i = 0; i < points.size(); i++) {
        Marker* item = static_cast<Marker*>(items.at(i));
        const QPointF& point = points.at(i);
        const QRectF& rect = item->boundingRect();
        item->setPoint(point);
        item->setPos(point.x()-rect.width()/2,point.y()-rect.height()/2);
        if(!clipRect().contains(point)) {
            item->setVisible(false);
        }
        else {
            item->setVisible(true);
        }
    }

    prepareGeometryChange();
    m_rect = clipRect();
    XYChartItem::setLayout(points);
}


void ScatterChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void ScatterChartItem::setPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_items.childItems()) {
           static_cast<Marker*>(item)->setPen(pen);
    }
}

void ScatterChartItem::setBrush(const QBrush& brush)
{
    foreach(QGraphicsItem* item , m_items.childItems()) {
            static_cast<Marker*>(item)->setBrush(brush);
     }
}

void ScatterChartItem::handleUpdated()
{

    int count = m_items.childItems().count();

    if(count==0) return;

    bool recreate = m_size != m_series->size() || m_shape != m_series->shape();

    //TODO: only rewrite on size change

    m_size = m_series->size();
    m_shape = m_series->shape();

    if(recreate){
        deletePoints(count);
        createPoints(count);
    }

    setPen(m_series->pen());
    setBrush(m_series->brush());
}

#include "moc_scatterchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

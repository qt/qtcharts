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

#include "legendmarker_p.h"
#include "qxyseries.h"
#include "qxyseries_p.h"
#include "qlegend.h"
#include "qbarseries.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "qareaseries.h"
#include "qareaseries_p.h"
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarker::LegendMarker(QAbstractSeries *series, QLegend *legend) : QGraphicsObject(legend),
m_series(series),
m_markerRect(0,0,10.0,10.0),
m_boundingRect(0,0,0,0),
m_legend(legend),
m_textItem(new QGraphicsSimpleTextItem(this)),
m_rectItem(new QGraphicsRectItem(this))
{
    //setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    m_rectItem->setRect(m_markerRect);
    updateLayout();
}

void LegendMarker::setPen(const QPen &pen)
{
    m_textItem->setPen(pen);
    updateLayout();
}

QPen LegendMarker::pen() const
{
    return m_textItem->pen();
}

void LegendMarker::setBrush(const QBrush &brush)
{
    m_rectItem->setBrush(brush);
}

QBrush LegendMarker::brush() const
{
    return m_rectItem->brush();
}

void LegendMarker::setLabel(const QString name)
{
    m_textItem->setText(name);
    updateLayout();
}

void LegendMarker::setSize(const QSize& size)
{
    m_markerRect = QRectF(0,0,size.width(),size.height());
}

QString LegendMarker::label() const
{
    return m_textItem->text();
}

void LegendMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}

QRectF LegendMarker::boundingRect() const
{
    return m_boundingRect;
}

void LegendMarker::updateLayout()
{

    static const qreal margin = 2;
    static const qreal space = 4;

    const QRectF& textRect = m_textItem->boundingRect();
    prepareGeometryChange();
    m_boundingRect = QRectF(0,0,m_markerRect.width() + 2*margin + space + textRect.width(),qMax(m_markerRect.height()+2*margin,textRect.height()+2*margin));
    m_textItem->setPos(m_markerRect.width() + space + margin,m_boundingRect.height()/2 - textRect.height()/2);
    m_rectItem->setPos(margin,m_boundingRect.height()/2 - m_markerRect.height()/2);

}

void LegendMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    qDebug()<<"Not implemented"; //TODO: selected signal removed for now
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AreaLegendMarker::AreaLegendMarker(QAreaSeries *series,QLegend *legend) : LegendMarker(series,legend),
m_series(series)
{
    //QObject::connect(this, SIGNAL(selected()), series, SIGNAL(selected()));
    QObject::connect(series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
    updated();
}

void AreaLegendMarker::updated()
{
    setBrush(m_series->brush());
    setLabel(m_series->name());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BarLegendMarker::BarLegendMarker(QBarSeries *barseries,QBarSet *barset, QLegend *legend) : LegendMarker(barseries,legend),
m_barset(barset)
{
    //QObject::connect(this, SIGNAL(selected()),barset->d_ptr.data(), SIGNAL(selected()));
    QObject::connect(barset->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(updated()));
    updated();
}

void BarLegendMarker::updated()
{
    setBrush(m_barset->brush());
    setLabel(m_barset->name());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PieLegendMarker::PieLegendMarker(QPieSeries* series,QPieSlice *pieslice, QLegend *legend) : LegendMarker(series,legend),
m_pieslice(pieslice)
{
    //QObject::connect(this, SIGNAL(selected()),pieslice, SIGNAL(clicked()));
    QObject::connect(pieslice, SIGNAL(changed()), this, SLOT(updated()));
    updated();
}

void PieLegendMarker::updated()
{
    setBrush(m_pieslice->brush());
    setLabel(m_pieslice->label());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

XYLegendMarker::XYLegendMarker(QXYSeries *series, QLegend *legend) : LegendMarker(series,legend),
m_series(series)
{
    //QObject::connect(this, SIGNAL(selected()), series, SIGNAL(selected()));
    QObject::connect(series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
    updated();
}

void XYLegendMarker::updated()
{
    setLabel(m_series->name());

    if(m_series->type()== QAbstractSeries::SeriesTypeScatter)
    {
        setBrush(m_series->brush());

    }
    else {
        setBrush(QBrush(m_series->pen().color()));
    }
}

#include "moc_legendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

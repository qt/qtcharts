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

#include "legendmarkeritem_p.h"
#include "qxyseries.h"
#include "qxyseries_p.h"
#include "qlegend.h"
#include "qabstractbarseries.h"
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

LegendMarkerItem::LegendMarkerItem(QAbstractSeries *series, QGraphicsObject *parent) :
    QGraphicsObject(parent),
    m_series(series),
    m_markerRect(0,0,10.0,10.0),
    m_boundingRect(0,0,0,0),
    m_textItem(new QGraphicsSimpleTextItem(this)),
    m_rectItem(new QGraphicsRectItem(this)),
    m_margin(4),
    m_space(4)
{
    //setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    m_rectItem->setRect(m_markerRect);
}

void LegendMarkerItem::setPen(const QPen &pen)
{
    m_rectItem->setPen(pen);
}

QPen LegendMarkerItem::pen() const
{
    return m_rectItem->pen();
}

void LegendMarkerItem::setBrush(const QBrush &brush)
{
    m_rectItem->setBrush(brush);
}

QBrush LegendMarkerItem::brush() const
{
    return m_rectItem->brush();
}

void LegendMarkerItem::setFont(const QFont &font)
{
    m_textItem->setFont(font);
    QFontMetrics fn(font);
    m_markerRect = QRectF(0,0,fn.height()/2,fn.height()/2);
    updateGeometry();
}

QFont LegendMarkerItem::font() const
{
    return m_textItem->font();
}

void LegendMarkerItem::setLabel(const QString label)
{
    m_text = label;
    updateGeometry();
}

QString LegendMarkerItem::label() const
{
    return m_text;
}

QRectF LegendMarkerItem::boundingRect() const
{
    return m_boundingRect;
}

void LegendMarkerItem::setLabelBrush(const QBrush &brush)
{
    m_textItem->setBrush(brush);
}

QBrush LegendMarkerItem::labelBrush() const
{
    return m_textItem->brush();
}


void LegendMarkerItem::setGeometry(const QRectF& rect)
{
    QFontMetrics fn (font());

    int width = rect.width();
    qreal x = m_margin + m_markerRect.width() +  m_space + m_margin;
    qreal y = qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin);

    if (fn.boundingRect(m_text).width() + x > width)
    {
        QString string = m_text + "...";
        while(fn.boundingRect(string).width() + x > width && string.length() > 3)
            string.remove(string.length() - 4, 1);
        m_textItem->setText(string);
    }
    else
        m_textItem->setText(m_text);

    const QRectF& textRect = m_textItem->boundingRect();


    m_textItem->setPos(x-m_margin,y/2 - textRect.height()/2);
    m_rectItem->setRect(m_markerRect);
    m_rectItem->setPos(m_margin,y/2  - m_markerRect.height()/2);

    prepareGeometryChange();
    m_boundingRect = QRectF(0,0,x+textRect.width()+m_margin,y);
}

void LegendMarkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}

QSizeF LegendMarkerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_textItem->font());
    QSizeF sh;

      switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        case Qt::PreferredSize:
            sh = QSizeF(fn.boundingRect(m_text).width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        default:
          break;
      }

      return sh;
}

void LegendMarkerItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "LegendMarkerItem::mousePressEvent";
    QGraphicsObject::mousePressEvent(event);
    //TODO: selected signal removed for now
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AreaLegendMarkerItem::AreaLegendMarkerItem(QAreaSeries *series,QLegend *legend) : LegendMarkerItem(series,legend),
m_series(series)
{
    //QObject::connect(this, SIGNAL(selected()), series, SIGNAL(selected()));
//    QObject::connect(series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
//    QObject::connect(series, SIGNAL(nameChanged()), this, SLOT(updated()));
    updated();
}

void AreaLegendMarkerItem::updated()
{
    setBrush(m_series->brush());
    setLabel(m_series->name());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BarLegendMarkerItem::BarLegendMarkerItem(QAbstractBarSeries *barseries,QBarSet *barset, QLegend *legend) : LegendMarkerItem(barseries,legend),
m_barset(barset)
{
    //QObject::connect(this, SIGNAL(selected()),barset->d_ptr.data(), SIGNAL(selected()));
//    QObject::connect(barset->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(updated()));
    updated();
}

void BarLegendMarkerItem::updated()
{
    setBrush(m_barset->brush());
    setLabel(m_barset->label());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PieLegendMarkerItem::PieLegendMarkerItem(QPieSeries* series,QPieSlice *pieslice, QLegend *legend) : LegendMarkerItem(series,legend),
m_pieslice(pieslice)
{
//    QObject::connect(pieslice, SIGNAL(labelChanged()), this, SLOT(updated()));
//    QObject::connect(pieslice, SIGNAL(brushChanged()), this, SLOT(updated()));
    updated();
}

void PieLegendMarkerItem::updated()
{
    setBrush(m_pieslice->brush());
    setLabel(m_pieslice->label());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

XYLegendMarkerItem::XYLegendMarkerItem(QXYSeries *series, QLegend *legend) : LegendMarkerItem(series,legend),
m_series(series)
{
    //QObject::connect(this, SIGNAL(selected()), series, SIGNAL(selected()));
//    QObject::connect(series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
//    QObject::connect(series, SIGNAL(nameChanged()), this, SLOT(updated()));
    updated();
}

void XYLegendMarkerItem::updated()
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

#include "moc_legendmarkeritem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

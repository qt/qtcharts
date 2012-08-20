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

LegendMarker::LegendMarker(QAbstractSeries *series, QLegend *legend) :
    QGraphicsObject(legend),
    m_series(series),
    m_markerRect(0,0,10.0,10.0),
    m_boundingRect(0,0,0,0),
    m_legend(legend),
    m_textItem(new QGraphicsSimpleTextItem(this)),
    m_rectItem(new QGraphicsRectItem(this)),
    m_margin(2),
    m_space(4)
{
    //setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    m_rectItem->setRect(m_markerRect);
}

void LegendMarker::setPen(const QPen &pen)
{
    m_rectItem->setPen(pen);
}

QPen LegendMarker::pen() const
{
    return m_rectItem->pen();
}

void LegendMarker::setBrush(const QBrush &brush)
{
    m_rectItem->setBrush(brush);
}

QBrush LegendMarker::brush() const
{
    return m_rectItem->brush();
}

void LegendMarker::setFont(const QFont &font)
{
    m_textItem->setFont(font);
    QFontMetrics fn(font);
    m_markerRect = QRectF(0,0,fn.height()/2,fn.height()/2);
    updateGeometry();
}

QFont LegendMarker::font() const
{
    return m_textItem->font();
}

void LegendMarker::setLabel(const QString label)
{
    m_textItem->setText(label);
}

QString LegendMarker::label() const
{
    return m_textItem->text();
}

QRectF LegendMarker::boundingRect() const
{
    return m_boundingRect;
}

void LegendMarker::setLabelBrush(const QBrush &brush)
{
    m_textItem->setBrush(brush);
}

QBrush LegendMarker::labelBrush() const
{
    return m_textItem->brush();
}


void LegendMarker::setGeometry(const QRectF& rect)
{
    const QRectF& textRect = m_textItem->boundingRect();

    m_textItem->setPos(m_markerRect.width() + m_space + m_margin,rect.height()/2 - textRect.height()/2);
    m_rectItem->setRect(m_markerRect);
    m_rectItem->setPos(m_margin,rect.height()/2 - m_markerRect.height()/2);

    prepareGeometryChange();
    m_boundingRect = rect;
}

void LegendMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}


QSizeF LegendMarker::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_textItem->font());
    QSizeF sh;

      switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width(),fn.height());
            break;
        case Qt::PreferredSize:
            sh = QSizeF(fn.boundingRect(m_textItem->text()).width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        default:
          break;
      }

      return sh;
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
    QObject::connect(series, SIGNAL(nameChanged()), this, SLOT(updated()));
    updated();
}

void AreaLegendMarker::updated()
{
    setBrush(m_series->brush());
    setLabel(m_series->name());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BarLegendMarker::BarLegendMarker(QAbstractBarSeries *barseries,QBarSet *barset, QLegend *legend) : LegendMarker(barseries,legend),
m_barset(barset)
{
    //QObject::connect(this, SIGNAL(selected()),barset->d_ptr.data(), SIGNAL(selected()));
    QObject::connect(barset->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(updated()));
    updated();
}

void BarLegendMarker::updated()
{
    setBrush(m_barset->brush());
    setLabel(m_barset->label());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PieLegendMarker::PieLegendMarker(QPieSeries* series,QPieSlice *pieslice, QLegend *legend) : LegendMarker(series,legend),
m_pieslice(pieslice)
{
    QObject::connect(pieslice, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::connect(pieslice, SIGNAL(brushChanged()), this, SLOT(updated()));
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
    QObject::connect(series, SIGNAL(nameChanged()), this, SLOT(updated()));
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

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

#include "qchartglobal.h"
#include "legendmarker_p.h"
#include <qpieslice.h>
#include <qbarset.h>
#include <qxyseries.h>
#include <qareaseries.h>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QGraphicsSimpleTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarker::LegendMarker(QSeries *series, QGraphicsItem *parent) : QGraphicsObject(parent),
    m_pos(0,0),
    m_size(0,0),
    m_boundingRect(0,0,0,0),
    m_markerBoundingRect(0,0,0,0),
    m_series(series),
    m_barset(0),
    m_pieslice(0),
    m_textItem(new QGraphicsSimpleTextItem(this))
{
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
}

LegendMarker::LegendMarker(QSeries *series, QBarSet *barset, QGraphicsItem *parent) : QGraphicsObject(parent),
    m_pos(0,0),
    m_size(0,0),
    m_boundingRect(0,0,0,0),
    m_markerBoundingRect(0,0,0,0),
    m_series(series),
    m_barset(barset),
    m_pieslice(0),
    m_textItem(new QGraphicsSimpleTextItem(this))
{
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
}

LegendMarker::LegendMarker(QSeries *series, QPieSlice *pieslice, QGraphicsItem *parent) : QGraphicsObject(parent),
    m_pos(0,0),
    m_size(0,0),
    m_boundingRect(0,0,0,0),
    m_markerBoundingRect(0,0,0,0),
    m_series(series),
    m_barset(0),
    m_pieslice(pieslice),
    m_textItem(new QGraphicsSimpleTextItem(this))
{
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
}

void LegendMarker::setPos(qreal x, qreal y)
{
    m_pos = QPointF(x,y);
    layoutChanged();
}

void LegendMarker::setPen(const QPen &pen)
{
    m_pen = pen;
}

QPen LegendMarker::pen() const
{
    return m_pen;
}

void LegendMarker::setBrush(const QBrush &brush)
{
    m_brush = brush;
}

QBrush LegendMarker::brush() const
{
    return m_brush;
}

void LegendMarker::setName(const QString name)
{
    m_textItem->setText(name);
    layoutChanged();
}

QString LegendMarker::name() const
{
    return m_textItem->text();
}

QSeries* LegendMarker::series() const
{
    return m_series;
}

void LegendMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(m_markerBoundingRect);
}

QRectF LegendMarker::boundingRect() const
{
    return m_boundingRect;
}

void LegendMarker::layoutChanged()
{
    QSizeF markerSize(10,10);
    qreal margin = 2;

    m_size.setHeight(markerSize.height() + 2 * margin);
    m_size.setWidth(m_textItem->boundingRect().width() + markerSize.width() + 3 * margin);

    m_boundingRect = QRectF(m_pos.x(),m_pos.y(),m_size.width(),m_size.height());

    m_markerBoundingRect = QRectF(m_pos.x() + margin, m_pos.y() + margin, markerSize.width(),markerSize.height());

    m_textItem->setPos(m_pos.x() + markerSize.width() + 2 * margin, m_pos.y() + margin);
}

void LegendMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_series->type()) {
    case QSeries::SeriesTypeLine:
    case QSeries::SeriesTypeArea:
    case QSeries::SeriesTypeScatter:
    case QSeries::SeriesTypeSpline: {
        emit clicked(m_series,event->button());
        break;
        }
    case QSeries::SeriesTypeBar:
    case QSeries::SeriesTypeStackedBar:
    case QSeries::SeriesTypePercentBar: {
        emit clicked(m_barset,event->button());
        break;
        }
    case QSeries::SeriesTypePie: {
        emit clicked(m_pieslice,event->button());
        break;
        }
    default: {
        break;
        }
    }
}

void LegendMarker::changed()
{
    switch (m_series->type()) {
    case QSeries::SeriesTypeArea: {
        QAreaSeries* s = static_cast<QAreaSeries*> (m_series);
        setPen(s->pen());
        setBrush(s->brush());
        setName(s->name());
        break;
    }
    case QSeries::SeriesTypeLine:
    case QSeries::SeriesTypeScatter:
    case QSeries::SeriesTypeSpline: {
        QXYSeries* s = static_cast<QXYSeries*> (m_series);
        setPen(s->pen());
        setBrush(s->brush());
        setName(s->name());
        break;
        }
    case QSeries::SeriesTypeBar:
    case QSeries::SeriesTypeStackedBar:
    case QSeries::SeriesTypePercentBar: {
        setPen(m_barset->pen());
        setBrush(m_barset->brush());
        setName(m_barset->name());
        break;
        }
    case QSeries::SeriesTypePie: {
        setBrush(m_pieslice->brush());
        setName(m_pieslice->label());
        break;
        }
    default: {
        break;
        }
    }
}

#include "moc_legendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

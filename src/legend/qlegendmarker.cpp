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

#include "qlegendmarker.h"
#include "qlegendmarker_p.h"
#include "legendmarkeritem_p.h"
#include <QDebug>
#include <QFontMetrics>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QLegendMarker::QLegendMarker(QAbstractSeries* series, QObject *parent) :
    QObject(parent),
    d_ptr(new QLegendMarkerPrivate(series, this))
{
}

QLegendMarker::~QLegendMarker()
{
}

QString QLegendMarker::label() const
{
    return d_ptr->m_label;
}

void QLegendMarker::setLabel(const QString &label)
{
    d_ptr->m_label = label;
}

QBrush QLegendMarker::labelBrush() const
{
    return d_ptr->m_labelBrush;
}

void QLegendMarker::setLabelBrush(const QBrush &brush)
{
    d_ptr->m_labelBrush = brush;
}

QFont QLegendMarker::font() const
{
    return d_ptr->m_font;
}

void QLegendMarker::setFont(const QFont &font)
{
    d_ptr->m_font = font;
}

QPen QLegendMarker::pen() const
{
    return d_ptr->m_pen;
}

void QLegendMarker::setPen(const QPen &pen)
{
    d_ptr->m_pen = pen;
}

QBrush QLegendMarker::brush() const
{
    return d_ptr->m_brush;
}

void QLegendMarker::setBrush(const QBrush &brush)
{
    d_ptr->m_brush = brush;
}

bool QLegendMarker::isVisible() const
{
    return d_ptr->m_visible;
}

void QLegendMarker::setVisible(bool visible)
{
    d_ptr->m_visible = visible;
}

QAbstractSeries* QLegendMarker::series()
{
    return d_ptr->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QLegendMarkerPrivate::QLegendMarkerPrivate(QAbstractSeries *series, QLegendMarker *q) :
    q_ptr(q),
    m_series(series)
{
    m_item = new LegendMarkerItem(m_series,this);
}

void QLegendMarkerPrivate::setGeometry(const QRectF& rect)
{
    QFontMetrics fn (m_font);


    int width = rect.width();
    qreal x = m_margin + m_markerRect.width() +  m_space + m_margin;
    qreal y = qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin);

    if (fn.boundingRect(m_label).width() + x > width)
    {
        QString string = m_label + "...";
        while(fn.boundingRect(string).width() + x > width && string.length() > 3)
            string.remove(string.length() - 4, 1);
        m_textItem->setText(string);
    }
    else
        m_textItem->setText(m_label);

    const QRectF& textRect = m_textItem->boundingRect();


    m_textItem->setPos(x-m_margin,y/2 - textRect.height()/2);
    m_rectItem->setRect(m_markerRect);
    m_rectItem->setPos(m_margin,y/2  - m_markerRect.height()/2);

    prepareGeometryChange();
    m_boundingRect = QRectF(0,0,x+textRect.width()+m_margin,y);
}

QRectF QLegendMarkerPrivate::boundingRect() const
{
    return m_boundingRect;
}

void QLegendMarkerPrivate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}

QSizeF QLegendMarkerPrivate::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_textItem->font());
    QSizeF sh;

      switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        case Qt::PreferredSize:
            sh = QSizeF(fn.boundingRect(m_label).width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        default:
          break;
      }

      return sh;
}

void QLegendMarkerPrivate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "QLegendMarkerPrivate::mousePressEvent" << event;
    QGraphicsObject::mousePressEvent(event);
    //TODO: selected signal removed for now
}


#include "moc_qlegendmarker.cpp"
#include "moc_qlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

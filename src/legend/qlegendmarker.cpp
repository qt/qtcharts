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
/*
QLegendMarker::QLegendMarker(QAbstractSeries* series, QObject *parent) :
    QObject(parent),
    d_ptr(new QLegendMarkerPrivate(series, this))
{
}
*/
QLegendMarker::QLegendMarker(QLegendMarkerPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
QLegendMarkerPrivate::QLegendMarkerPrivate(QAbstractSeries *series, QLegendMarker *q) :
    q_ptr(q),
    m_series(series)
{
    m_item = new LegendMarkerItem(m_series);
}
*/
QLegendMarkerPrivate::QLegendMarkerPrivate(QLegendMarker *q) :
    q_ptr(q)
{
    qDebug() << "QLegendMarkerPrivate created";
    m_item = new LegendMarkerItem(this);
}

QLegendMarkerPrivate::~QLegendMarkerPrivate()
{
}

void QLegendMarkerPrivate::handleMousePressEvent(QGraphicsSceneEvent *event)
{
    // Just emit clicked signal for now
    Q_UNUSED(event);
    Q_Q(QLegendMarker);
    emit q->clicked();
}


#include "moc_qlegendmarker.cpp"
#include "moc_qlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

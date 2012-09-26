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
#include "qlegend.h"
#include <QDebug>
#include <QFontMetrics>
#include <QGraphicsSceneEvent>

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
    return d_ptr->label();
}

void QLegendMarker::setLabel(const QString &label)
{
    d_ptr->setLabel(label);
}

QBrush QLegendMarker::labelBrush() const
{
    return d_ptr->labelBrush();
}

void QLegendMarker::setLabelBrush(const QBrush &brush)
{
    d_ptr->setLabelBrush(brush);
}

QFont QLegendMarker::font() const
{
    return d_ptr->font();
}

void QLegendMarker::setFont(const QFont &font)
{
    d_ptr->setFont(font);
}

QPen QLegendMarker::pen() const
{
    return d_ptr->pen();
}

void QLegendMarker::setPen(const QPen &pen)
{
    d_ptr->setPen(pen);
}

QBrush QLegendMarker::brush() const
{
    return d_ptr->brush();
}

void QLegendMarker::setBrush(const QBrush &brush)
{
    d_ptr->setBrush(brush);
}

bool QLegendMarker::isVisible() const
{
    return d_ptr->isVisible();
}

void QLegendMarker::setVisible(bool visible)
{
    d_ptr->setVisible(visible);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QLegendMarkerPrivate::QLegendMarkerPrivate(QLegendMarker *q, QLegend *legend) :
    q_ptr(q),
    m_legend(legend)
{
//    qDebug() << "QLegendMarkerPrivate created";
    m_item = new LegendMarkerItem(this);
}

QLegendMarkerPrivate::~QLegendMarkerPrivate()
{
}

void QLegendMarkerPrivate::handleMousePressEvent(QGraphicsSceneEvent *event)
{
    // Just emit clicked signal for now (our default logic for events)
    // This could propably be on the LegendMarkerItem?
    // TODO: how to handle scrolling vs clicking? drag event?
    event->accept();
    Q_Q(QLegendMarker);
    emit q->clicked();
}

void QLegendMarkerPrivate::setPen(const QPen &pen)
{
    m_item->setPen(pen);
}

QPen QLegendMarkerPrivate::pen() const
{
    return m_item->pen();
}

void QLegendMarkerPrivate::setBrush(const QBrush &brush)
{
    m_item->setBrush(brush);
}

QBrush QLegendMarkerPrivate::brush() const
{
    return m_item->brush();
}

void QLegendMarkerPrivate::setFont(const QFont &font)
{
    m_item->setFont(font);
}

QFont QLegendMarkerPrivate::font() const
{
    return m_item->font();
}

void QLegendMarkerPrivate::setLabel(const QString label)
{
    m_item->setLabel(label);
}

QString QLegendMarkerPrivate::label() const
{
    return m_item->label();
}

void QLegendMarkerPrivate::setLabelBrush(const QBrush &brush)
{
    m_item->setLabelBrush(brush);
}

QBrush QLegendMarkerPrivate::labelBrush() const
{
    return m_item->labelBrush();
}

bool QLegendMarkerPrivate::isVisible() const
{
    return m_item->isVisible();
}

void QLegendMarkerPrivate::setVisible(bool visible)
{
    m_item->setVisible(visible);
}


#include "moc_qlegendmarker.cpp"
#include "moc_qlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

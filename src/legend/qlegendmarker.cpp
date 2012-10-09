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
#include "qlegend_p.h"
#include "legendlayout_p.h"
#include <QFontMetrics>
#include <QGraphicsSceneEvent>
#include <QAbstractSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QLegendMarker::QLegendMarker(QLegendMarkerPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
    d_ptr->m_item->setVisible(d_ptr->series()->isVisible());
}

QLegendMarker::~QLegendMarker()
{
}

QString QLegendMarker::label() const
{
    return d_ptr->m_item->label();
}

void QLegendMarker::setLabel(const QString &label)
{
    d_ptr->m_item->setLabel(label);
}

QBrush QLegendMarker::labelBrush() const
{
    return d_ptr->m_item->labelBrush();
}

void QLegendMarker::setLabelBrush(const QBrush &brush)
{
    d_ptr->m_item->setLabelBrush(brush);
}

QFont QLegendMarker::font() const
{
    return d_ptr->m_item->font();
}

void QLegendMarker::setFont(const QFont &font)
{
    d_ptr->m_item->setFont(font);
}

QPen QLegendMarker::pen() const
{
    return d_ptr->m_item->pen();
}

void QLegendMarker::setPen(const QPen &pen)
{
    d_ptr->m_item->setPen(pen);
}

QBrush QLegendMarker::brush() const
{
    return d_ptr->m_item->brush();
}

void QLegendMarker::setBrush(const QBrush &brush)
{
    d_ptr->m_item->setBrush(brush);
}

bool QLegendMarker::isVisible() const
{
    return d_ptr->m_item->isVisible();
}

void QLegendMarker::setVisible(bool visible)
{
    d_ptr->m_item->setVisible(visible);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QLegendMarkerPrivate::QLegendMarkerPrivate(QLegendMarker *q, QLegend *legend) :
    q_ptr(q),
    m_legend(legend)
{
    m_item = new LegendMarkerItem(this);
//    m_item->setVisible(q->series()->isVisible());
}

QLegendMarkerPrivate::~QLegendMarkerPrivate()
{
}

void QLegendMarkerPrivate::invalidateLegend()
{
    m_legend->d_ptr->m_layout->invalidate();
}



#include "moc_qlegendmarker.cpp"
#include "moc_qlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

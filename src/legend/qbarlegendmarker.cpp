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

#include "qbarlegendmarker.h"
#include "qbarlegendmarker_p.h"
#include <QAbstractBarSeries>
#include <QBarSet>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarLegendMarker
    \brief QBarLegendMarker object
    \mainclass

    QBarLegendMarker is related to QAbstractBarSeries derived classes. With bar series, each marker is related to one QBarSet.

    \sa QLegend QAbstractBarSeries QBarSet
*/

/*!
  \fn virtual LegendMarkerType QBarLegendMarker::type()
  Returns QLegendMarker::LegendMarkerTypeBar
*/

/*!
  \internal
  Constructor
*/
QBarLegendMarker::QBarLegendMarker(QAbstractBarSeries *series, QBarSet *barset, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QBarLegendMarkerPrivate(this,series,barset,legend), parent)
{
    d_ptr->updated();
}

/*!
  Desturctor
*/
QBarLegendMarker::~QBarLegendMarker()
{
}

/*!
    \internal
*/
QBarLegendMarker::QBarLegendMarker(QBarLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
  Returns the related series of marker
*/
QAbstractBarSeries *QBarLegendMarker::series()
{
    Q_D(QBarLegendMarker);
    return d->m_series;
}

/*!
  Returns the related barset of marker
*/
QBarSet* QBarLegendMarker::barset()
{
    Q_D(QBarLegendMarker);
    return d->m_barset;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarLegendMarkerPrivate::QBarLegendMarkerPrivate(QBarLegendMarker *q, QAbstractBarSeries *series, QBarSet *barset, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series),
    m_barset(barset)
{
    QObject::connect(m_barset, SIGNAL(penChanged()), this, SLOT(updated()));
    QObject::connect(m_barset, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::connect(m_barset, SIGNAL(brushChanged()), this, SLOT(updated()));
}

QBarLegendMarkerPrivate::~QBarLegendMarkerPrivate()
{
}

QAbstractBarSeries* QBarLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QBarLegendMarkerPrivate::relatedObject()
{
    return m_barset;
}

void QBarLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;
    bool penChanged = false;

    if (!m_customPen && (m_item->pen() != m_barset->pen())) {
        m_item->setPen(m_barset->pen());
        penChanged = true;
    }
    if (!m_customBrush && (m_item->brush() != m_barset->brush())) {
        m_item->setBrush(m_barset->brush());
        brushChanged = true;
    }
    if (!m_customLabel && (m_item->label() != m_barset->label())) {
        m_item->setLabel(m_barset->label());
        labelChanged = true;
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
    if (penChanged)
        emit q_ptr->penChanged();
}

#include "moc_qbarlegendmarker.cpp"
#include "moc_qbarlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


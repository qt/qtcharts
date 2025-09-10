// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QPieLegendMarker>
#include <private/qpielegendmarker_p.h>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_BEGIN_NAMESPACE

/*!
    \class QPieLegendMarker
    \inmodule QtCharts
    \brief The QPieLegendMarker class is a legend marker for a pie series.

    A pie legend marker is related to QPieSeries. With a pie series, each slice of the pie
    is related to one marker in the legend.

    \sa QLegend, QPieSeries, QPieSlice
*/

/*!
  \fn virtual LegendMarkerType QPieLegendMarker::type()
  \reimp
*/

/*!
  \internal
*/
QPieLegendMarker::QPieLegendMarker(QPieSeries *series, QPieSlice *slice, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QPieLegendMarkerPrivate(this,series,slice,legend), parent)
{
    d_ptr->updated();
}

/*!
    Removes the legend marker for a pie series.
*/
QPieLegendMarker::~QPieLegendMarker()
{
}

/*!
    \internal
*/
QPieLegendMarker::QPieLegendMarker(QPieLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
    \reimp
*/
QPieSeries* QPieLegendMarker::series()
{
    Q_D(QPieLegendMarker);
    return d->m_series;
}

/*!
    Returns the slice of the pie related to the marker.
*/
QPieSlice* QPieLegendMarker::slice()
{
    Q_D(QPieLegendMarker);
    return d->m_slice;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPieLegendMarkerPrivate::QPieLegendMarkerPrivate(QPieLegendMarker *q, QPieSeries *series, QPieSlice *slice, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series),
    m_slice(slice)
{
    QObject::connect(m_slice, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::connect(m_slice, SIGNAL(brushChanged()), this, SLOT(updated()));
    QObject::connect(m_slice, SIGNAL(penChanged()), this, SLOT(updated()));
}

QPieLegendMarkerPrivate::~QPieLegendMarkerPrivate()
{
}

QPieSeries* QPieLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QPieLegendMarkerPrivate::relatedObject()
{
    return m_slice;
}

void QPieLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;
    bool penChanged = false;

    if (!m_customPen && (m_item->pen() != m_slice->pen())) {
        m_item->setPen(m_slice->pen());
        penChanged = true;
    }
    if (!m_customBrush && (m_item->brush() != m_slice->brush())) {
        m_item->setBrush(m_slice->brush());
        brushChanged = true;
    }
    if (!m_customLabel && (m_item->label() != m_slice->label())) {
        m_item->setLabel(m_slice->label());
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

QT_END_NAMESPACE

#include "moc_qpielegendmarker.cpp"
#include "moc_qpielegendmarker_p.cpp"

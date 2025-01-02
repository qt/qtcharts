// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QBoxPlotLegendMarker>
#include <private/qboxplotlegendmarker_p.h>
#include <QtCharts/QBoxPlotSeries>
#include <private/qboxplotseries_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QBoxPlotLegendMarker
    \inmodule QtCharts
    \brief The QBoxPlotLegendMarker class is a legend marker for a box plot series.

    A box plot legend marker is related to a QBoxPlotSeries object.

    \sa QLegend, QBoxPlotSeries
*/

/*!
  \fn virtual LegendMarkerType QBoxPlotLegendMarker::type()
  \reimp
*/

/*!
  \internal
*/
QBoxPlotLegendMarker::QBoxPlotLegendMarker(QBoxPlotSeries *series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QBoxPlotLegendMarkerPrivate(this,series,legend), parent)
{
    d_ptr->updated();
}

/*!
    Removes the legend marker for a box plot series.
*/
QBoxPlotLegendMarker::~QBoxPlotLegendMarker()
{
}

/*!
    \internal
*/
QBoxPlotLegendMarker::QBoxPlotLegendMarker(QBoxPlotLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
    \reimp
*/
QBoxPlotSeries* QBoxPlotLegendMarker::series()
{
    Q_D(QBoxPlotLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxPlotLegendMarkerPrivate::QBoxPlotLegendMarkerPrivate(QBoxPlotLegendMarker *q, QBoxPlotSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series)
{
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(updated()));
}

QBoxPlotLegendMarkerPrivate::~QBoxPlotLegendMarkerPrivate()
{
}

QAbstractSeries* QBoxPlotLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QBoxPlotLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QBoxPlotLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customLabel && (m_item->label() != m_series->name())) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }
    if (!m_customBrush && (m_item->brush() != m_series->brush())) {
        m_item->setBrush(m_series->brush());
        brushChanged = true;
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

QT_END_NAMESPACE

#include "moc_qboxplotlegendmarker.cpp"
#include "moc_qboxplotlegendmarker_p.cpp"

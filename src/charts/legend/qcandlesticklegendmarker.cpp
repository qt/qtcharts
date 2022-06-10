// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QCandlestickLegendMarker>
#include <private/legendmarkeritem_p.h>
#include <private/qcandlesticklegendmarker_p.h>
#include <private/qcandlestickseries_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QCandlestickLegendMarker
    \inmodule QtCharts
    \since 5.8
    \brief The QCandlestickLegendMarker class is a legend marker for a candlestick series.

    QCandlestickLegendMarker is related to QCandlestickSeries, so that one candlestick series
    results in one marker.

    \sa QLegend, QCandlestickSeries
*/

/*!
    \internal
*/
QCandlestickLegendMarker::QCandlestickLegendMarker(QCandlestickSeries *series, QLegend *legend,
                                                   QObject *parent)
    : QLegendMarker(*new QCandlestickLegendMarkerPrivate(this, series, legend), parent)
{
    Q_D(QCandlestickLegendMarker);

    d->updated();
}

QCandlestickLegendMarker::~QCandlestickLegendMarker()
{
}

/*!
    \reimp
*/
QLegendMarker::LegendMarkerType QCandlestickLegendMarker::type()
{
    return LegendMarkerTypeCandlestick;
}

/*!
    \reimp
*/
QCandlestickSeries* QCandlestickLegendMarker::series()
{
    Q_D(QCandlestickLegendMarker);

    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

QCandlestickLegendMarkerPrivate::QCandlestickLegendMarkerPrivate(QCandlestickLegendMarker *q,
                                                                 QCandlestickSeries *series,
                                                                 QLegend *legend)
    : QLegendMarkerPrivate(q, legend),
      q_ptr(q),
      m_series(series)
{
    QObject::connect(m_item, SIGNAL(markerRectChanged()), this, SLOT(updated()));
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(updated()));
}

QCandlestickLegendMarkerPrivate::~QCandlestickLegendMarkerPrivate()
{
}

QAbstractSeries* QCandlestickLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QCandlestickLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QCandlestickLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customLabel && (m_item->label() != m_series->name())) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }
    if (!m_customBrush) {
        QLinearGradient gradient;
        gradient.setStart(0.0, 0.0);
        gradient.setFinalStop(m_item->markerRect().width(), m_item->markerRect().height());
        gradient.setColorAt(0.0, m_series->increasingColor());
        gradient.setColorAt(0.49, m_series->increasingColor());
        gradient.setColorAt(0.50, m_series->decreasingColor());
        gradient.setColorAt(1.0, m_series->decreasingColor());

        QBrush brush(gradient);
        if (m_item->brush() != brush) {
            m_item->setBrush(brush);
            brushChanged = true;
        }
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

QT_END_NAMESPACE

#include "moc_qcandlesticklegendmarker.cpp"
#include "moc_qcandlesticklegendmarker_p.cpp"

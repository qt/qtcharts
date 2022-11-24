/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QXYLegendMarker>
#include <private/qxylegendmarker_p.h>
#include <private/qxyseries_p.h>
#include <QtCharts/QXYSeries>
#if QT_CONFIG(charts_scatter_chart)
#include <QtCharts/QScatterSeries>
#endif

QT_BEGIN_NAMESPACE

/*!
    \class QXYLegendMarker
    \inmodule QtCharts
    \brief The QXYLegendMarker class is a legend marker for a line, spline, or scatter series.

    An XY legend marker is related to QXYSeries derived classes: QLineSeries, QSplineSeries,
    and QScatterSeries. Each marker is related to one series.

    \sa QLegend, QXYSeries, QSplineSeries, QScatterSeries, QLineSeries
*/

/*!
  \fn virtual LegendMarkerType QXYLegendMarker::type()
  \reimp
*/

/*!
  \internal
*/
QXYLegendMarker::QXYLegendMarker(QXYSeries *series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QXYLegendMarkerPrivate(this,series,legend), parent)
{
    d_ptr->updated();
}

/*!
    Removes the legend marker for a line, spline, or scatter series.
*/
QXYLegendMarker::~QXYLegendMarker()
{
}

/*!
    \internal
*/
QXYLegendMarker::QXYLegendMarker(QXYLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
    \reimp
*/
QXYSeries* QXYLegendMarker::series()
{
    Q_D(QXYLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QXYLegendMarkerPrivate::QXYLegendMarkerPrivate(QXYLegendMarker *q, QXYSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series)
{
    connect(m_series->d_func(), &QXYSeriesPrivate::seriesUpdated,
            this, &QXYLegendMarkerPrivate::updated);
    connect(m_series, &QXYSeries::nameChanged, this, &QXYLegendMarkerPrivate::updated);
}

QXYLegendMarkerPrivate::~QXYLegendMarkerPrivate()
{
}

QAbstractSeries* QXYLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QXYLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QXYLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customLabel && (m_item->label() != m_series->name())) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }
#if QT_CONFIG(charts_scatter_chart)
    if (m_series->type()== QAbstractSeries::SeriesTypeScatter)  {
        if (!m_customBrush && (m_item->brush() != m_series->brush())) {
            m_item->setBrush(m_series->brush());
            brushChanged = true;
        }
        if (m_item->effectiveMarkerShape() == QLegend::MarkerShapeFromSeries) {
            QScatterSeries *scatter = static_cast<QScatterSeries *>(m_series);
            if (scatter) {
                const bool shapeChangeNeeded =
                        (scatter->markerShape() == QScatterSeries::MarkerShapeCircle
                        && m_item->itemType() != LegendMarkerItem::TypeCircle)
                        || (scatter->markerShape() == QScatterSeries::MarkerShapeRectangle
                            && m_item->itemType() != LegendMarkerItem::TypeRect);
                if (shapeChangeNeeded || scatter->markerSize() != m_item->markerRect().width())
                    m_item->updateMarkerShapeAndSize();
            }
        }
    } else
#endif
    {
        QBrush emptyBrush;
        if (!m_customBrush
            && (m_item->brush() == emptyBrush
                || m_item->brush().color() != m_series->pen().color())) {
            m_item->setBrush(QBrush(m_series->pen().color()));
            brushChanged = true;
        }

        if (m_item->effectiveMarkerShape() == QLegend::MarkerShapeFromSeries
            && m_series->markerSize() != m_item->markerRect().width()) {
            m_item->updateMarkerShapeAndSize();
        }
    }
    m_item->setSeriesBrush(m_series->brush());
    m_item->setSeriesPen(m_series->pen());

    if (m_item->effectiveMarkerShape() == QLegend::MarkerShapeFromSeries)
        m_item->setSeriesLightMarker(m_series->lightMarker());

    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

QT_END_NAMESPACE

#include "moc_qxylegendmarker.cpp"
#include "moc_qxylegendmarker_p.cpp"

/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#include <QtCharts/QPieLegendMarker>
#include <private/qpielegendmarker_p.h>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QPieLegendMarker
    \inmodule Qt Charts
    \brief QLegendMarker subclass for pie series.

    QPieLegendMarker is related to QPieSeries. With QPieSeries, each slice of pie is related to one marker in QLegend.

    \sa QLegend, QPieSeries, QPieSlice
*/

/*!
  \fn virtual LegendMarkerType QPieLegendMarker::type()
  Returns QLegendMarker::LegendMarkerTypePie
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
  Destructor
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
  Returns the related series of marker.
*/
QPieSeries* QPieLegendMarker::series()
{
    Q_D(QPieLegendMarker);
    return d->m_series;
}

/*!
  Returns the related slice of marker.
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

#include "moc_qpielegendmarker.cpp"
#include "moc_qpielegendmarker_p.cpp"

QT_CHARTS_END_NAMESPACE

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

#include "qxylegendmarker.h"
#include "qxylegendmarker_p.h"
#include "qxyseries_p.h"
#include <QXYSeries>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QXYLegendMarker::QXYLegendMarker(QXYSeries* series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QXYLegendMarkerPrivate(this,series,legend), parent)
{
}

QXYLegendMarker::~QXYLegendMarker()
{
//    qDebug() << "deleting xy marker" << this;
}

/*!
    \internal
*/
QXYLegendMarker::QXYLegendMarker(QXYLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

QXYSeries* QXYLegendMarker::series()
{
    Q_D(QXYLegendMarker);
    return d->m_series;
}

QXYSeries* QXYLegendMarker::peerObject()
{
    Q_D(QXYLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QXYLegendMarkerPrivate::QXYLegendMarkerPrivate(QXYLegendMarker *q, QXYSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    m_series(series)
{
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(updated()));
    updated();
}

QXYLegendMarkerPrivate::~QXYLegendMarkerPrivate()
{
    QObject::disconnect(m_series->d_func(), SIGNAL(updated()), this, SLOT(updated()));
    QObject::disconnect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
}

void QXYLegendMarkerPrivate::updated()
{
    m_item->setLabel(m_series->name());

    if (m_series->type()== QAbstractSeries::SeriesTypeScatter)  {
        m_item->setBrush(m_series->brush());
    } else {
        m_item->setBrush(QBrush(m_series->pen().color()));
    }
}

#include "moc_qxylegendmarker.cpp"
#include "moc_qxylegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


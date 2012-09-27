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

#include "qarealegendmarker.h"
#include "qarealegendmarker_p.h"
#include "qareaseries_p.h"
#include <QAreaSeries>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QAreaLegendMarker::QAreaLegendMarker(QAreaSeries* series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QAreaLegendMarkerPrivate(this,series,legend), parent)
{
}

QAreaLegendMarker::~QAreaLegendMarker()
{
//    qDebug() << "deleting Area marker" << this;
}

/*!
    \internal
*/
QAreaLegendMarker::QAreaLegendMarker(QAreaLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

QAreaSeries* QAreaLegendMarker::series()
{
    Q_D(QAreaLegendMarker);
    return d->m_series;
}

QAreaSeries* QAreaLegendMarker::peerObject()
{
    Q_D(QAreaLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAreaLegendMarkerPrivate::QAreaLegendMarkerPrivate(QAreaLegendMarker *q, QAreaSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    m_series(series)
{
    qDebug() << "QAreaLegendMarkerPrivate created";
    QObject::connect(m_series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    updated();
}

QAreaLegendMarkerPrivate::~QAreaLegendMarkerPrivate()
{
    QObject::disconnect(m_series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
    QObject::disconnect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
}

void QAreaLegendMarkerPrivate::updated()
{
    qDebug() << "QAreaLegendMarkerPrivate::updated";
    m_item->setBrush(m_series->brush());
    m_item->setLabel(m_series->name());
}

#include "moc_qarealegendmarker.cpp"
#include "moc_qarealegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

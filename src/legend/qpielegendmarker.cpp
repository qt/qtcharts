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

#include "qpielegendmarker.h"
#include "qpielegendmarker_p.h"
#include <QPieSeries>
#include <QPieSlice>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieLegendMarker::QPieLegendMarker(QPieSeries* series, QPieSlice* slice, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QPieLegendMarkerPrivate(this,series,slice,legend), parent)
{
}

QPieLegendMarker::~QPieLegendMarker()
{
//    qDebug() << "deleting pie marker" << this;
}

/*!
    \internal
*/
QPieLegendMarker::QPieLegendMarker(QPieLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

QPieSeries* QPieLegendMarker::series()
{
    Q_D(QPieLegendMarker);
    return d->m_series;
}

QPieSlice* QPieLegendMarker::slice()
{
    Q_D(QPieLegendMarker);
    return d->m_slice;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPieLegendMarkerPrivate::QPieLegendMarkerPrivate(QPieLegendMarker *q, QPieSeries *series, QPieSlice *slice, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    m_series(series),
    m_slice(slice)
{
    QObject::connect(m_slice, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::connect(m_slice, SIGNAL(brushChanged()), this, SLOT(updated()));
    QObject::connect(m_slice, SIGNAL(penChanged()), this, SLOT(updated()));
    updated();
}

QPieLegendMarkerPrivate::~QPieLegendMarkerPrivate()
{
    QObject::disconnect(m_slice, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::disconnect(m_slice, SIGNAL(brushChanged()), this, SLOT(updated()));
    QObject::disconnect(m_slice, SIGNAL(penChanged()), this, SLOT(updated()));
}

void QPieLegendMarkerPrivate::updated()
{
    m_item->setPen(m_slice->pen());
    m_item->setBrush(m_slice->brush());
    m_item->setLabel(m_slice->label());
}

#include "moc_qpielegendmarker.cpp"
#include "moc_qpielegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

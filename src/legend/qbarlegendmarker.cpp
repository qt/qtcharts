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
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarLegendMarker::QBarLegendMarker(QAbstractBarSeries* series, QBarSet* barset, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QBarLegendMarkerPrivate(this,series,barset,legend), parent)
{
}

QBarLegendMarker::~QBarLegendMarker()
{
//    qDebug() << "deleting bar marker" << this;
}

/*!
    \internal
*/
QBarLegendMarker::QBarLegendMarker(QBarLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

QAbstractBarSeries *QBarLegendMarker::series()
{
    Q_D(QBarLegendMarker);
    return d->m_series;
}

QBarSet* QBarLegendMarker::barset()
{
    Q_D(QBarLegendMarker);
    return d->m_barset;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarLegendMarkerPrivate::QBarLegendMarkerPrivate(QBarLegendMarker *q, QAbstractBarSeries *series, QBarSet *barset, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    m_series(series),
    m_barset(barset)
{
    QObject::connect(m_barset, SIGNAL(penChanged()), this, SLOT(updated()));
    QObject::connect(m_barset, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::connect(m_barset, SIGNAL(brushChanged()), this, SLOT(updated()));
    updated();
}

QBarLegendMarkerPrivate::~QBarLegendMarkerPrivate()
{
    QObject::disconnect(m_barset, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::disconnect(m_barset, SIGNAL(brushChanged()), this, SLOT(updated()));
    QObject::disconnect(m_barset, SIGNAL(penChanged()), this, SLOT(updated()));
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
    m_item->setPen(m_barset->pen());
    m_item->setBrush(m_barset->brush());
    m_item->setLabel(m_barset->label());
}

#include "moc_qbarlegendmarker.cpp"
#include "moc_qbarlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


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
#include <QPieSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieLegendMarker::QPieLegendMarker(QPieSeries* series, QPieSlice* slice, QObject *parent) :
    QLegendMarker(series, parent),
    m_slice(slice)
{
    QObject::connect(slice, SIGNAL(labelChanged()), this, SLOT(updated()));
    QObject::connect(slice, SIGNAL(brushChanged()), this, SLOT(updated()));
    updated();
}

QPieSlice* QPieLegendMarker::peerObject()
{
    return m_slice;
}

void QPieLegendMarker::updated()
{
    // TODO: to PIMPL.
    setBrush(m_slice->brush());
    setLabel(m_slice->label());
}

#include "moc_qpielegendmarker.cpp"
//#include "moc_qpielegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

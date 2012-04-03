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

#include "customslice.h"

QTCOMMERCIALCHART_USE_NAMESPACE

CustomSlice::CustomSlice(qreal value, QString label)
    :QPieSlice(value, label)
{
    connect(this, SIGNAL(hoverEnter()), this, SLOT(handleHoverEnter()));
    connect(this, SIGNAL(hoverLeave()), this, SLOT(handleHoverLeave()));
}

QBrush CustomSlice::originalBrush()
{
    return m_originalBrush;
}

void CustomSlice::handleHoverEnter()
{
    QBrush brush = this->brush();
    m_originalBrush = brush;
    brush.setColor(brush.color().lighter());
    setBrush(brush);
}

void CustomSlice::handleHoverLeave()
{
    setBrush(m_originalBrush);
}

#include "moc_customslice.cpp"

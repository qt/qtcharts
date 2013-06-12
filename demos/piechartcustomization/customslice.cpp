/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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

CustomSlice::CustomSlice(QString label, qreal value)
    : QPieSlice(label, value)
{
    connect(this, SIGNAL(hovered(bool)), this, SLOT(showHighlight(bool)));
}

QBrush CustomSlice::originalBrush()
{
    return m_originalBrush;
}

void CustomSlice::showHighlight(bool show)
{
    if (show) {
        QBrush brush = this->brush();
        m_originalBrush = brush;
        brush.setColor(brush.color().lighter());
        setBrush(brush);
    } else {
        setBrush(m_originalBrush);
    }
}

#include "moc_customslice.cpp"

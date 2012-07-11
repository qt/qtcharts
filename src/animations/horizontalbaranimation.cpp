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

#include "horizontalbaranimation_p.h"
#include "abstractbarchartitem_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalBarAnimation::HorizontalBarAnimation(AbstractBarChartItem *item) :
    AbstractBarAnimation(item)
{
}

HorizontalBarAnimation::~HorizontalBarAnimation()
{

}


QVariant HorizontalBarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    // TODO:
    Q_UNUSED(from);
    Q_UNUSED(to);
    Q_UNUSED(progress);
    return to;
}

#include "moc_horizontalbaranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

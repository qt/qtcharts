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

#include "percentbaranimation_p.h"
#include "percentbarchartitem_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarAnimation::PercentBarAnimation(PercentBarChartItem *item)
    : AbstractBarAnimation(item)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

PercentBarAnimation::~PercentBarAnimation()
{
}

QVariant PercentBarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QVector<QRectF> startVector = qVariantValue<QVector<QRectF> >(from);
    QVector<QRectF> endVector = qVariantValue<QVector<QRectF> >(to);
    QVector<QRectF> result;

    Q_ASSERT(startVector.count() == endVector.count());

    qreal yAxis = m_item->geometry().height() + m_item->geometry().y();

    for (int i = 0; i < startVector.count(); i++) {
        qreal w = endVector[i].width();
        qreal h = startVector[i].height() + ((endVector[i].height() - startVector[i].height()) * progress);
        qreal x = endVector[i].topLeft().x();
        qreal y = yAxis + ((endVector[i].topLeft().y() - yAxis) * progress);

        QRectF value(x, y, w, h);
        result << value.normalized();
    }
    return qVariantFromValue(result);
}

#include "moc_percentbaranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

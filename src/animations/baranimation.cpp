/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#include "baranimation_p.h"
#include "abstractbarchartitem_p.h"

Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarAnimation::BarAnimation(AbstractBarChartItem *item)
    : ChartAnimation(item),
      m_item(item)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

BarAnimation::~BarAnimation()
{
}

QVariant BarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QVector<QRectF> startVector = qvariant_cast<QVector<QRectF> >(from);
    QVector<QRectF> endVector = qvariant_cast<QVector<QRectF> >(to);
    QVector<QRectF> result;

    Q_ASSERT(startVector.count() == endVector.count());

    for (int i = 0; i < startVector.count(); i++) {
        QRectF start = startVector[i].normalized();
        QRectF end = endVector[i].normalized();
        qreal x1 = start.left() + progress * (end.left() - start.left());
        qreal x2 = start.right() + progress * (end.right() - start.right());
        qreal y1 = start.top() + progress * (end.top() - start.top());
        qreal y2 = start.bottom() + progress * (end.bottom() - start.bottom());

        QRectF value(QPointF(x1, y1), QPointF(x2, y2));
        result << value.normalized();
    }
    return qVariantFromValue(result);
}

void BarAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround

        QVector<QRectF> layout = qvariant_cast<QVector<QRectF> >(value);
        m_item->setLayout(layout);
    }
}

void BarAnimation::setup(const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout)
{
    QVariantAnimation::KeyValues value;
    setKeyValues(value); //workaround for wrong interpolation call
    setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    setKeyValueAt(1.0, qVariantFromValue(newLayout));
}

#include "moc_baranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/baranimation_p.h>
#include <private/abstractbarchartitem_p.h>


QT_BEGIN_NAMESPACE

BarAnimation::BarAnimation(AbstractBarChartItem *item, int duration, QEasingCurve &curve)
    : ChartAnimation(item),
      m_item(item)
{
    setDuration(duration);
    setEasingCurve(curve);
}

BarAnimation::~BarAnimation()
{
}

QVariant BarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    const QList<QRectF> startList = qvariant_cast<QList<QRectF>>(from);
    const QList<QRectF> endList = qvariant_cast<QList<QRectF>>(to);
    QList<QRectF> result;

    Q_ASSERT(startList.size() == endList.size());

    for (int i = 0; i < startList.size(); i++) {
        const QRectF start = startList[i].normalized();
        const QRectF end = endList[i].normalized();
        const qreal x1 = start.left() + progress * (end.left() - start.left());
        const qreal x2 = start.right() + progress * (end.right() - start.right());
        const qreal y1 = start.top() + progress * (end.top() - start.top());
        const qreal y2 = start.bottom() + progress * (end.bottom() - start.bottom());

        QRectF value(QPointF(x1, y1), QPointF(x2, y2));
        result << value.normalized();
    }
    return QVariant::fromValue(result);
}

void BarAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround

        const QList<QRectF> layout = qvariant_cast<QList<QRectF>>(value);
        m_item->setLayout(layout);
    }
}

void BarAnimation::setup(const QList<QRectF> &oldLayout, const QList<QRectF> &newLayout)
{
    QVariantAnimation::KeyValues value;
    setKeyValues(value); //workaround for wrong interpolation call
    setKeyValueAt(0.0, QVariant::fromValue(oldLayout));
    setKeyValueAt(1.0, QVariant::fromValue(newLayout));
}

QT_END_NAMESPACE

#include "moc_baranimation_p.cpp"

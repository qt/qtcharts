/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/baranimation_p.h>
#include <private/abstractbarchartitem_p.h>

Q_DECLARE_METATYPE(QList<QRectF>)

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

    Q_ASSERT(startList.count() == endList.count());

    for (int i = 0; i < startList.count(); i++) {
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

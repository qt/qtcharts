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

#include "abstractbaranimation_p.h"
#include "abstractbarchartitem_p.h"
#include <QTimer>
#include <QDebug>

Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AbstractBarAnimation::AbstractBarAnimation(AbstractBarChartItem *item)
    :ChartAnimation(item),
    m_item(item)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

AbstractBarAnimation::~AbstractBarAnimation()
{
}

QVariant AbstractBarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    Q_UNUSED(progress);
    qWarning() << "AbstractBarAnimation::interpolated called";
    return to;
}

void AbstractBarAnimation::updateCurrentValue(const QVariant &value)
{
    QVector<QRectF> layout = qVariantValue<QVector<QRectF> >(value);
    m_item->setLayout(layout);
}

void AbstractBarAnimation::setup(const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout)
{
    QVariantAnimation::KeyValues value;
    setKeyValues(value); //workaround for wrong interpolation call
    setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    setKeyValueAt(1.0, qVariantFromValue(newLayout));
}

#include "moc_abstractbaranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


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

#include "horizontalpercentbaranimation_p.h"
#include "abstractbarchartitem_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalPercentBarAnimation::HorizontalPercentBarAnimation(AbstractBarChartItem *item) :
    AbstractBarAnimation(item)
{
}

HorizontalPercentBarAnimation::~HorizontalPercentBarAnimation()
{

}


QVariant HorizontalPercentBarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QVector<QRectF> startVector = qvariant_cast<QVector<QRectF> >(from);
    QVector<QRectF> endVector = qvariant_cast<QVector<QRectF> >(to);
    QVector<QRectF> result;

    Q_ASSERT(startVector.count() == endVector.count());

    qreal xAxis = m_item->geometry().x();

    for (int i = 0; i < startVector.count(); i++) {
        qreal h = endVector[i].height();
        qreal w = endVector[i].width() * progress;
        qreal x = xAxis + ((endVector[i].left() - xAxis) * progress);
        qreal y = endVector[i].top();

        QRectF value(x, y, w, h);
        result << value.normalized();
    }
    return qVariantFromValue(result);
}

#include "moc_horizontalpercentbaranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

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
    QVector<QRectF> startVector = qVariantValue<QVector<QRectF> >(from);
    QVector<QRectF> endVector = qVariantValue<QVector<QRectF> >(to);
    QVector<QRectF> result;

    Q_ASSERT(startVector.count() == endVector.count());

    for(int i = 0; i < startVector.count(); i++) {
        QRectF start = startVector[i].normalized();
        QRectF end = endVector[i].normalized();

        qreal x;
        qreal y = end.top();
        qreal w;
        qreal h = end.height();

        if (endVector[i].width() < 0) {
            // Negative bar
            w = start.width() + ((end.width() - start.width()) * progress);
            x = endVector[i].right() - endVector[i].width() - w;
        } else {
            w = startVector[i].width() + ((endVector[i].width() - startVector[i].width()) * progress);
            x = end.left();
        }

        QRectF value(x,y,w,h);
        result << value.normalized();
    }
    return qVariantFromValue(result);
}

#include "moc_horizontalbaranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

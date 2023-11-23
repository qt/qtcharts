// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef LINEARROWITEM_P_H
#define LINEARROWITEM_P_H

#include <private/chartaxiselement_p.h>
#include <private/qabstractaxis_p.h>
#include <QtWidgets/QGraphicsLineItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT LineArrowItem: public QGraphicsLineItem
{
public:
    explicit LineArrowItem(ChartAxisElement *axis, QGraphicsItem *parent = 0)
        : QGraphicsLineItem(parent),
          m_axis(axis),
          m_axisOrientation(axis->axis()->orientation())
    {
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        m_axis->axisSelected();
        QGraphicsLineItem::mousePressEvent(event);
    }

    QRectF boundingRect() const override
    {
        return shape().boundingRect();
    }

    QPainterPath shape() const override
    {
        QPainterPath path = QGraphicsLineItem::shape();
        QRectF rect = path.boundingRect();
        path.addRect(rect.adjusted(0, 0, m_axisOrientation != Qt::Horizontal ? 8 : 0, m_axisOrientation != Qt::Vertical ? 8 : 0));
        return path;
    }

private:
    ChartAxisElement *m_axis;
    Qt::Orientation m_axisOrientation;
};

QT_END_NAMESPACE

#endif /* LINEARROWITEM_P_H */

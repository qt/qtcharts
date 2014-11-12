/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef LINEARROWITEM_P_H
#define LINEARROWITEM_P_H

#include <private/chartaxiselement_p.h>
#include <private/qabstractaxis_p.h>
#include <QtWidgets/QGraphicsLineItem>

QT_CHARTS_BEGIN_NAMESPACE

class LineArrowItem: public QGraphicsLineItem
{
public:
    explicit LineArrowItem(ChartAxisElement *axis, QGraphicsItem *parent = 0)
        : QGraphicsLineItem(parent),
          m_axis(axis),
          m_axisOrientation(axis->axis()->orientation())
    {
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        Q_UNUSED(event)
        m_axis->axisSelected();
    }

    QRectF boundingRect() const
    {
        return shape().boundingRect();
    }

    QPainterPath shape() const
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

QT_CHARTS_END_NAMESPACE

#endif /* LINEARROWITEM_P_H */

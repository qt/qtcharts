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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef PIESLICEITEM_H
#define PIESLICEITEM_H

#include "qchartglobal.h"
#include "charttheme_p.h"
#include "qpieseries.h"
#include "pieslicedata_p.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QColor>
#include <QPen>

#define PIESLICE_LABEL_GAP 5

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieChartItem;
class PieSliceLabel;
class QPieSlice;

class PieSliceItem : public QGraphicsObject
{
    Q_OBJECT

public:
    PieSliceItem(QGraphicsItem *parent = 0);
    ~PieSliceItem();

    // from QGraphicsItem
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setLayout(const PieSliceData &sliceData);
    static QPointF sliceCenter(QPointF point, qreal radius, QPieSlice *slice);

Q_SIGNALS:
    void clicked(Qt::MouseButtons buttons);
    void hovered(bool state);

private:
    void updateGeometry();
    QPainterPath slicePath(QPointF center, qreal radius, qreal startAngle, qreal angleSpan, qreal *centerAngle, QPointF *armStart);
    QPainterPath labelArmPath(QPointF start, qreal angle, qreal length, qreal textWidth, QPointF *textStart);

private:
    PieSliceData m_data;
    QRectF m_boundingRect;
    QPainterPath m_slicePath;
    QPainterPath m_labelArmPath;
    QRectF m_labelTextRect;
    bool m_hovered;

    friend class PieSliceAnimation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESLICEITEM_H

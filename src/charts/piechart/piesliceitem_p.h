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

#ifndef PIESLICEITEM_H
#define PIESLICEITEM_H

#include <QtCharts/QChartGlobal>
#include <private/charttheme_p.h>
#include <QtCharts/QPieSeries>
#include <private/pieslicedata_p.h>
#include <QtWidgets/QGraphicsItem>
#include <QtCore/QRectF>
#include <QtGui/QColor>
#include <QtGui/QPen>

#define PIESLICE_LABEL_GAP 5

QT_CHARTS_BEGIN_NAMESPACE
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
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void setLayout(const PieSliceData &sliceData);
    static QPointF sliceCenter(QPointF point, qreal radius, QPieSlice *slice);

Q_SIGNALS:
    void clicked(Qt::MouseButtons buttons);
    void hovered(bool state);
    void pressed(Qt::MouseButtons buttons);
    void released(Qt::MouseButtons buttons);
    void doubleClicked(Qt::MouseButtons buttons);

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
    QGraphicsTextItem *m_labelItem;

    bool m_mousePressed;

    friend class PieSliceAnimation;
};

QT_CHARTS_END_NAMESPACE

#endif // PIESLICEITEM_H

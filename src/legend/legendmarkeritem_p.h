/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef LEGENDMARKERITEM_P_H
#define LEGENDMARKERITEM_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsLayoutItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegendMarkerPrivate;

class LegendMarkerItem : public QGraphicsObject, public QGraphicsLayoutItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsLayoutItem)
public:
    explicit LegendMarkerItem(QLegendMarkerPrivate *marker, QGraphicsObject *parent = 0);
    ~LegendMarkerItem();

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setFont(const QFont &font);
    QFont font() const;

    void setLabel(const QString label);
    QString label() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setGeometry(const QRectF &rect);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QSizeF sizeHint (Qt::SizeHint which, const QSizeF &constraint) const;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

protected:
    QLegendMarkerPrivate *m_marker; // Knows
    QRectF m_markerRect;
    QRectF m_boundingRect;
    QGraphicsSimpleTextItem *m_textItem;
    QGraphicsRectItem *m_rectItem;
    qreal m_margin;
    qreal m_space;
    QString m_label;

    QBrush m_labelBrush;
    QFont m_font;
    QPen m_pen;
    QBrush m_brush;
    bool m_hovering;

    QPointF m_pressPos;

    friend class QLegendMarker;
    friend class QLegendMarkerPrivate;
    friend class LegendLayout;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // LEGENDMARKERITEM_P_H

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

#ifndef LEGENDMARKERITEM_P_H
#define LEGENDMARKERITEM_P_H

#include <QtCharts/QChartGlobal>
#include <QGraphicsObject>
#include <QtGui/QFont>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsLayoutItem>

QT_CHARTS_BEGIN_NAMESPACE

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
    QGraphicsTextItem *m_textItem;
    QGraphicsRectItem *m_rectItem;
    qreal m_margin;
    qreal m_space;
    QString m_label;

    QBrush m_labelBrush;
    QPen m_pen;
    QBrush m_brush;
    bool m_hovering;

    QPointF m_pressPos;

    friend class QLegendMarker;
    friend class QLegendMarkerPrivate;
    friend class LegendLayout;
};

QT_CHARTS_END_NAMESPACE

#endif // LEGENDMARKERITEM_P_H

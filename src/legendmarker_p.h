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

#ifndef LEGENDMARKER_P_H
#define LEGENDMARKER_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QBrush>
#include <QPen>
#include <QGraphicsSimpleTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSeries;
class QBarSet;
class QPieSlice;

// TODO: split this to 3 different markers for series, barset and pieslice. Current implementation is easier to misuse...
class LegendMarker : public QGraphicsObject
{
    Q_OBJECT

public:
    LegendMarker(QSeries *series, QGraphicsItem *parent = 0);
    LegendMarker(QSeries *series, QBarSet *barset, QGraphicsItem *parent = 0);
    LegendMarker(QSeries *series, QPieSlice *pieslice, QGraphicsItem *parent = 0);

    void setPos(qreal x, qreal y);

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setName(const QString name);
    QString name() const;

    QSeries* series() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    QRectF boundingRect() const;

    void layoutChanged();

public:
    // From QGraphicsObject
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked(QSeries *series, Qt::MouseButton button);
    void clicked(QBarSet *barset, Qt::MouseButton button);
    void clicked(QPieSlice *pieslice, Qt::MouseButton button);

public Q_SLOTS:
    void changed();

private:
    QPointF m_pos;
    QSize m_size;
    QRectF m_boundingRect;
    QRectF m_markerBoundingRect;
    QBrush m_brush;
    QPen m_pen;

    QSeries *m_series;
    QBarSet *m_barset;
    QPieSlice *m_pieslice;

    QGraphicsSimpleTextItem *m_textItem;

};

QTCOMMERCIALCHART_END_NAMESPACE
#endif // LEGENDMARKER_P_H

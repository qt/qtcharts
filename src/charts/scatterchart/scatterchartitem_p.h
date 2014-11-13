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

#ifndef SCATTERCHARTITEM_H
#define SCATTERCHARTITEM_H

#include <QtCharts/QChartGlobal>
#include <private/xychart_p.h>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsSceneMouseEvent>

QT_CHARTS_BEGIN_NAMESPACE

class QScatterSeries;

class ScatterChartItem : public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ScatterChartItem(QScatterSeries *series, QGraphicsItem *item = 0);

public:
    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

    void markerSelected(QGraphicsItem *item);
    void markerHovered(QGraphicsItem *item, bool state);
    void markerPressed(QGraphicsItem *item);
    void markerReleased(QGraphicsItem *item);
    void markerDoubleClicked(QGraphicsItem *item);

    void setMousePressed(bool pressed = true) {m_mousePressed = pressed;}
    bool mousePressed() {return m_mousePressed;}


public Q_SLOTS:
    void handleUpdated();

private:
    void createPoints(int count);
    void deletePoints(int count);

protected:
    void updateGeometry();

private:
    QScatterSeries *m_series;
    QGraphicsItemGroup m_items;
    bool m_visible;
    int m_shape;
    int m_size;
    QRectF m_rect;
    QMap<QGraphicsItem *, QPointF> m_markerMap;

    bool m_pointLabelsVisible;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;

    bool m_mousePressed;
};

class CircleMarker: public QGraphicsEllipseItem
{

public:
    CircleMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent)
        : QGraphicsEllipseItem(x, y, w, h, parent),
          m_parent(parent)
    {
        setAcceptHoverEvents(true);
        setFlag(QGraphicsItem::ItemIsSelectable);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsEllipseItem::mousePressEvent(event);
        m_parent->markerPressed(this);
        m_parent->setMousePressed();
    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)
    {
        QGraphicsEllipseItem::hoverEnterEvent(event);
        m_parent->markerHovered(this, true);
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
    {
        QGraphicsEllipseItem::hoverLeaveEvent(event);
        m_parent->markerHovered(this, false);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsEllipseItem::mouseReleaseEvent(event);
        m_parent->markerReleased(this);
        if (m_parent->mousePressed())
            m_parent->markerSelected(this);
        m_parent->setMousePressed(false);
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsEllipseItem::mouseDoubleClickEvent(event);
        m_parent->markerDoubleClicked(this);
    }

private:
    ScatterChartItem *m_parent;
};

class RectangleMarker: public QGraphicsRectItem
{

public:
    RectangleMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent)
        : QGraphicsRectItem(x, y, w, h, parent),
          m_parent(parent)
    {
        setAcceptHoverEvents(true);
        setFlag(QGraphicsItem::ItemIsSelectable);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsRectItem::mousePressEvent(event);
        m_parent->markerPressed(this);
        m_parent->setMousePressed();
    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)
    {
        QGraphicsRectItem::hoverEnterEvent(event);
        m_parent->markerHovered(this, true);
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
    {
        QGraphicsRectItem::hoverLeaveEvent(event);
        m_parent->markerHovered(this, false);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsRectItem::mouseReleaseEvent(event);
        m_parent->markerReleased(this);
        if (m_parent->mousePressed())
            m_parent->markerSelected(this);
        m_parent->setMousePressed(false);
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsRectItem::mouseDoubleClickEvent(event);
        m_parent->markerDoubleClicked(this);
    }

private:
    ScatterChartItem *m_parent;
};

QT_CHARTS_END_NAMESPACE

#endif // SCATTERPRESENTER_H

/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
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
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QScatterSeries;

class Q_CHARTS_PRIVATE_EXPORT ScatterChartItem : public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit ScatterChartItem(QScatterSeries *series, QGraphicsItem *item = 0);

public:
    //from QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

    void markerSelected(QGraphicsItem *item);
    void markerHovered(QGraphicsItem *item, bool state);
    void markerPressed(QGraphicsItem *item);
    void markerReleased(QGraphicsItem *item);
    void markerDoubleClicked(QGraphicsItem *item);
    void handleMarkerMouseReleaseEvent(QGraphicsItem *item);

    void setMousePressed(bool pressed = true) {m_mousePressed = pressed;}
    bool mousePressed() {return m_mousePressed;}


public Q_SLOTS:
    void handleSeriesUpdated() override;

private:
    void createPoints(int count);
    void deletePoints(int count);
    void resizeMarker(QGraphicsItem *marker, const int size);

protected:
    void updateGeometry() override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QScatterSeries *m_series;
    QGraphicsItemGroup m_items;
    bool m_visible;
    int m_markerShape;
    QRectF m_rect;
    QMap<QGraphicsItem *, QPointF> m_markerMap;

    bool m_pointsVisible;
    bool m_pointLabelsVisible;
    qreal m_markerSize;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

    QPointF m_lastHoveredPoint;
    QPointF m_lastMousePos;
    bool m_mousePressed;
};

template <class T>
class Q_CHARTS_PRIVATE_EXPORT ChartMarker : public T
{
public:
    explicit ChartMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent);
    explicit ChartMarker(ScatterChartItem *parent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ScatterChartItem *m_parent;
};

class Q_CHARTS_PRIVATE_EXPORT RotatedRectangleMarker : public ChartMarker<QGraphicsPolygonItem>
{
public:
    explicit RotatedRectangleMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent);

    static QPolygonF polygon(qreal x = 0.0, qreal y = 0.0, qreal w = 10.0, qreal h = 10.0);
};

class Q_CHARTS_PRIVATE_EXPORT TriangleMarker : public ChartMarker<QGraphicsPolygonItem>
{
public:
    explicit TriangleMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent);

    static QPolygonF polygon(qreal x = 0.0, qreal y = 0.0, qreal w = 10.0, qreal h = 10.0);
};

class Q_CHARTS_PRIVATE_EXPORT StarMarker : public ChartMarker<QGraphicsPolygonItem>
{
public:
    explicit StarMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent);

    static QPolygonF polygon(qreal x = 0.0, qreal y = 0.0, qreal w = 10.0, qreal h = 10.0);
};

class Q_CHARTS_PRIVATE_EXPORT PentagonMarker : public ChartMarker<QGraphicsPolygonItem>
{
public:
    explicit PentagonMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent);

    static QPolygonF polygon(qreal x = 0.0, qreal y = 0.0, qreal w = 10.0, qreal h = 10.0);
};


QT_END_NAMESPACE

#endif // SCATTERPRESENTER_H

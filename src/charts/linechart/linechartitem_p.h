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

#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include <QtCharts/QChartGlobal>
#include <private/xychart_p.h>
#include <QtCharts/QChart>
#include <QtGui/QPen>

QT_CHARTS_BEGIN_NAMESPACE

class QLineSeries;
class ChartPresenter;

class LineChartItem :  public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit LineChartItem(QLineSeries *series, QGraphicsItem *item = 0);
    ~LineChartItem() {}

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    QPainterPath path() const { return m_fullPath; }

public Q_SLOTS:
    void handleUpdated();

protected:
    void updateGeometry();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void suppressPoints() { m_pointsVisible = false; }
    void forceChartType(QChart::ChartType chartType) { m_chartType = chartType; }

private:
    QLineSeries *m_series;
    QPainterPath m_linePath;
    QPainterPath m_linePathPolarRight;
    QPainterPath m_linePathPolarLeft;
    QPainterPath m_fullPath;
    QPainterPath m_shapePath;

    QVector<QPointF> m_points;
    QRectF m_rect;
    QPen m_linePen;
    bool m_pointsVisible;
    QChart::ChartType m_chartType;

    bool m_pointLabelsVisible;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;

    QPointF m_lastMousePos;
    bool m_mousePressed;
};

QT_CHARTS_END_NAMESPACE

#endif

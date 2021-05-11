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

#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include <QtCharts/QChartGlobal>
#include <private/xychart_p.h>
#include <QtCharts/QChart>
#include <QtGui/QPen>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QLineSeries;
class ChartPresenter;

class Q_CHARTS_PRIVATE_EXPORT LineChartItem :  public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit LineChartItem(QLineSeries *series, QGraphicsItem *item = 0);
    ~LineChartItem() {}

    //from QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

    QPainterPath path() const { return m_fullPath; }

public Q_SLOTS:
    void handleSeriesUpdated() override;

protected:
    void updateGeometry() override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void suppressPoints() { m_pointsVisible = false; }
    void forceChartType(QChart::ChartType chartType) { m_chartType = chartType; }

private:
    QLineSeries *m_series;
    QPainterPath m_linePath;
    QPainterPath m_linePathPolarRight;
    QPainterPath m_linePathPolarLeft;
    QPainterPath m_fullPath;
    QPainterPath m_shapePath;

    QList<QPointF> m_linePoints;
    QRectF m_rect;
    QPen m_linePen;
    bool m_pointsVisible;
    QChart::ChartType m_chartType;

    bool m_pointLabelsVisible;
    qreal m_markerSize;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

    QPointF m_lastMousePos;
    bool m_mousePressed;
};

QT_END_NAMESPACE

#endif

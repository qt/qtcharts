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

#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
    Q_OBJECT
public:
    explicit Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0, QLineSeries *series = 0);
    ~Chart();

public slots:
    void clickPoint(const QPointF &point);

public:
    void handlePointMove(const QPoint &point);
    void setPointClicked(bool clicked);

private:
    qreal distance(const QPointF &p1, const QPointF &p2);
    QLineSeries *m_series;
    QPointF m_movingPoint;

    //Boolean value to determine if an actual point in the
    //series is clicked.
    bool m_clicked;
};

#endif // CHART_H

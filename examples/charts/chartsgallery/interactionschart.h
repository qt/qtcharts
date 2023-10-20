// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef INTERACTIONSCHART_H
#define INTERACTIONSCHART_H

#include <QChart>

QT_FORWARD_DECLARE_CLASS(QLineSeries)

class InteractionsChart : public QChart
{
    Q_OBJECT
public:
    explicit InteractionsChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {}, QLineSeries *series = nullptr);

public slots:
    void clickPoint(const QPointF &point);

public:
    void handlePointMove(const QPoint &point);
    void setPointClicked(bool clicked);

private:
    qreal distance(const QPointF &p1, const QPointF &p2);

    QLineSeries *m_series = nullptr;
    QPointF m_movingPoint;

    // Boolean value to determine if an actual point in the series is clicked
    bool m_clicked = false;
};

#endif

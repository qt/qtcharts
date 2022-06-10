// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef GRID_H_
#define GRID_H_

#include "model.h"
#include <QtWidgets/QGraphicsWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QGraphicsGridLayout;
QT_END_NAMESPACE

class Chart;

QT_BEGIN_NAMESPACE
class QChart;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class Grid : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum State { NoState = 0, ZoomState, ScrollState};

    Grid(int size, QGraphicsItem *parent = 0);
    ~Grid();

    QList<QChart *> charts();
    void createCharts(const QString &category = QString());
    void createCharts(const QString &category, const QString &subcategory, const QString &name);
    void replaceChart(QChart *oldChart, Chart *newChart);
    void setState(State state);
    State state() const { return m_state; };
    void setRubberPen(const QPen &pen);
    void setSize(int size);
    int size() const {return m_size;}

Q_SIGNALS:
    void chartSelected(QChart *chart);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void clear();

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    int m_size;
    DataTable m_dataTable;
    QHash<QChart *, int> m_chartHash;
    QHash<int, QChart *> m_chartHashRev;
    State m_state;
    State m_currentState;
    QPointF m_origin;
    QGraphicsRectItem *m_rubberBand;
    QGraphicsGridLayout *m_gridLayout;
};

#endif /* GRID_H_ */

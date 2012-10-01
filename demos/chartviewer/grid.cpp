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

#include "grid.h"
#include "charts.h"
#include <qchart.h>
#include <QGraphicsGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Grid::Grid(int size,QGraphicsItem *parent):QGraphicsWidget(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_size(size),
    m_dataTable(Model::generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    m_rubberBand(new QGraphicsRectItem()),
    m_gridLayout(new QGraphicsGridLayout())
{
    setLayout(m_gridLayout);
    m_rubberBand->setParentItem(this);
    m_rubberBand->setVisible(false);
    m_rubberBand->setZValue(2);
}

Grid::~Grid()
{

}

void Grid::createCharts()
{
    clear();

    Charts::ChartList list = Charts::chartList();

    for (int i = 0; i < m_size * m_size; ++i) {
        QChart *chart = 0;
        if (i < list.size()) {
            chart = list.at(i)->createChart(m_dataTable);
        }
        else {
            chart = new QChart();
            chart->setTitle(QObject::tr("Empty"));
        }

        m_gridLayout->addItem(chart, i / m_size, i % m_size);
        m_chartHash[chart] = i;
    }

}

void Grid::createCharts(const QString& category)
{
    clear();

    QChart *qchart(0);
    Charts::ChartList list = Charts::chartList();

    int j = 0;
    for (int i = 0; i < list.size(); ++i) {
        Chart *chart = list.at(i);
        if (chart->category() == category && j < m_size * m_size) {
            qchart = list.at(i)->createChart(m_dataTable);
            m_gridLayout->addItem(qchart, j / m_size, j % m_size);
            m_chartHash[qchart] = j;
            j++;
        }
    }
    for (; j < m_size * m_size; ++j) {
        qchart = new QChart();
        qchart->setTitle(QObject::tr("Empty"));
        m_gridLayout->addItem(qchart, j / m_size, j % m_size);
        m_chartHash[qchart] = j;
    }

    m_gridLayout->activate();
}

void Grid::clear()
{
    for (int i = 0; i < m_gridLayout->count(); ++i) {
        m_gridLayout->removeAt(i);
    }

    qDeleteAll(m_chartHash.keys());
    m_chartHash.clear();
}

QList<QChart*> Grid::charts()
{
    return m_chartHash.keys();
}

void Grid::setState(State state)
{
    m_state = state;
}

void Grid::setRubberPen(const QPen& pen)
{
    m_rubberBand->setPen(pen);
}

void Grid::replaceChart(QChart* oldChart, Chart* newChart)
{
    int index = m_chartHash[oldChart];
    //not in 4.7.2 m_baseLayout->removeItem(qchart);
    for (int i = 0; i < m_gridLayout->count(); ++i) {
        if (m_gridLayout->itemAt(i) == oldChart) {
            m_gridLayout->removeAt(i);
            break;
        }
    }
    m_chartHash.remove(oldChart);
    QChart *chart = newChart->createChart(m_dataTable);
    m_gridLayout->addItem(chart, index / m_size, index % m_size);
    m_chartHash[chart] = index;
    delete oldChart;
}

void Grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        m_origin = event->pos();
        m_currentState = NoState;

        foreach (QChart *chart, charts()) {

            QRectF geometryRect = chart->geometry();
            QRectF plotArea = chart->plotArea();
            plotArea.translate(geometryRect.topLeft());
            if (plotArea.contains(m_origin)) {
                m_currentState = m_state;
                if (m_currentState == NoState) emit chartSelected(chart);
                break;
            }
        }
        if (m_currentState == ZoomState) {
            m_rubberBand->setRect(QRectF(m_origin, QSize()));
            m_rubberBand->setVisible(true);
        }

        event->accept();
    }

    if (event->button() == Qt::RightButton) {
        m_origin = event->pos();
        m_currentState = m_state;
    }
}

void Grid::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_currentState != NoState) {

        foreach (QChart *chart, charts()) {

            QRectF geometryRect = chart->geometry();
            QRectF plotArea = chart->plotArea();
            plotArea.translate(geometryRect.topLeft());

            if (plotArea.contains(m_origin)) {
                if (m_currentState == ScrollState) {
                    QPointF delta = m_origin - event->pos();
                    chart->scroll(delta.x(), -delta.y());
                }
                if (m_currentState == ZoomState && plotArea.contains(event->pos()))
                    m_rubberBand->setRect(QRectF(m_origin, event->pos()).normalized());
                break;
            }
        }
        if (m_currentState == ScrollState)
            m_origin = event->pos();
        event->accept();
    }
}

void Grid::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_currentState == ZoomState) {
            m_rubberBand->setVisible(false);

            foreach (QChart *chart, charts()) {

                QRectF geometryRect = chart->geometry();
                QRectF plotArea = chart->plotArea();
                plotArea.translate(geometryRect.topLeft());

                if (plotArea.contains(m_origin)) {
                    QRectF rect = m_rubberBand->rect();
                    rect.translate(-geometryRect.topLeft());
                    chart->zoomIn(rect);
                    break;
                }
            }
        }

        m_currentState = NoState;
        event->accept();
    }

    if (event->button() == Qt::RightButton) {

        if (m_currentState == ZoomState) {
            foreach (QChart *chart, charts()) {

                QRectF geometryRect = chart->geometry();
                QRectF plotArea = chart->plotArea();
                plotArea.translate(geometryRect.topLeft());

                if (plotArea.contains(m_origin)) {
                    chart->zoomOut();
                    break;
                }
            }
        }
    }
}

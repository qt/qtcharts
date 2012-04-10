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

#include "mainwindow.h"
#include <QChartView>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QChart *chart = new QChart();
    chart->setTitle("Click to remove scatter point");

    m_scatter = new QScatterSeries();
    for(qreal x(0.5); x <= 4.0; x += 0.5) {
        for(qreal y(0.5); y <= 4.0; y += 0.5) {
            *m_scatter << QPointF(x, y);
        }
    }

    chart->addSeries(m_scatter);
    chart->axisX()->setRange(0, 4.5);
    chart->axisY()->setRange(0, 4.5);

    connect(m_scatter, SIGNAL(clicked(QPointF)), this, SLOT(handleClickedPoint(QPointF)));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleClickedPoint(const QPointF& point)
{
    m_scatter->remove(point);
}

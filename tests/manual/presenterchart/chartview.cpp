// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chartview.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCore/QRandomGenerator>

ChartView::ChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent),
      m_index(-1),
      m_chart(chart)
{
    m_chart->setTitle("Charts presenter");
    m_chart->setDropShadowEnabled(false);
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_timer.setInterval(3000);

    //![1]
    QLineSeries *series0 = new QLineSeries();
    series0->setName("line");

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter");

    QSplineSeries *series2 = new QSplineSeries();
    series2->setName("spline");

    QAreaSeries *series3 = new QAreaSeries(series0);
    series3->setName("area");
    //![1]

    //![2]
    int numPoints = 10;

    for (int x = 0; x <= numPoints; ++x) {
        qreal y = QRandomGenerator::global()->bounded(100);
        series0->append(x, y);
        series1->append(x, y);
        series2->append(x, y);
    }
    //![2]

    //![3]
    m_series << series0;
    m_titles << m_chart->title() + ": LineChart";
    m_series << series1;
    m_titles << m_chart->title() + ": ScatterChart";
    m_series << series2;
    m_titles << m_chart->title() + ": SplineChart";
    m_series << series3;
    m_titles << m_chart->title() + ": AreaChart";
    //![3]

    m_timer.start();
    handleTimeout();
}

ChartView::~ChartView()
{
    if (m_series.size() == 0)
        return;
    m_chart->removeSeries(m_series.at(m_index));
    m_series.removeLast();  //remove QAreaSeries instance since they will be deleted when QLineSeries instance is gone
    qDeleteAll(m_series);
}

//![4]
void ChartView::handleTimeout()
{
    if (m_series.size() == 0)
        return;
    if (m_index >= 0)
        m_chart->removeSeries(m_series.at(m_index));
    m_index++;
    m_index = m_index % m_series.size();
    m_chart->addSeries(m_series.at(m_index));
    m_chart->setTitle(m_titles.at(m_index));
    m_chart->createDefaultAxes();
}
//![4]

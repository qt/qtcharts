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

#include "chartview.h"
#include <QSplineSeries>
#include <QTime>

ChartView::ChartView(QWidget* parent):QChartView(parent),
m_step(1),
m_x(0),
m_y(1)
{
    QTime now = QTime::currentTime();
    qsrand((uint)now.msec());
    setChartTitle("Three random line charts");

    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    m_timer.setInterval(1000);

    m_series0 = new QLineSeries(this);
    QPen blue(Qt::blue);
    blue.setWidth(3);
    m_series0->setPen(blue);


    m_series1 = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series1->setPen(green);

    m_series0->append(m_x,m_y);
    m_series1->append(m_x,m_y);

    setChartTitle("Simple EKG chart");
    addSeries(m_series0);
    addSeries(m_series1);
    axisY()->setRange(-5,5);
    axisX()->setRange(-9,1);
    axisX()->setTicksCount(11);
    m_timer.start();
}

ChartView::~ChartView()
{

}

void ChartView::handleTimeout()
{
    m_x+=m_step;
    m_y = qrand() % 5 - 2.5;
    m_series0->append(m_x,m_y);
    m_series1->append(m_x,m_y);
    if(m_x>=10)
    {
        m_series0->remove(m_x-10);
        m_series1->remove(m_x-10);
    }
    scrollRight();
}

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

#include "chart.h"
#include <QAbstractAxis>
#include <QSplineSeries>
#include <QValuesAxis>
#include <QTime>
#include <QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    :QChart(parent, wFlags),
    m_step(0),
    m_axis(new QValuesAxis),
    m_x(5),
    m_y(1)
{
    qsrand((uint) QTime::currentTime().msec());

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_timer.setInterval(1000);

    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis,m_series);
    m_axis->setTicksCount(5);
    axisX()->setRange(0, 10);
    axisY()->setRange(-5, 10);

    m_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    qreal x = plotArea().width()/m_axis->ticksCount();
    qreal y =(m_axis->max() - m_axis->min())/m_axis->ticksCount();
    m_x += y;
    m_y = qrand() % 5 - 2.5;
    m_series->append(m_x, m_y);
    scroll(x,0);
    if(m_x==100) m_timer.stop();
}

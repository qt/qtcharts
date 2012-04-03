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

#include "splinewidget.h"
#include "qchartview.h"
#include "qlineseries.h"
#include <QGridLayout>
#include <QPushButton>
#include "qchartaxis.h"
#include <qmath.h>
#include <QTime>

QTCOMMERCIALCHART_USE_NAMESPACE

SplineWidget::SplineWidget(QWidget *parent)
    : QWidget(parent)
{
//    qsrand(time(NULL));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //! [1]
    //create QSplineSeries
    series = new QSplineSeries(this);
    //! [1]

    //! [2]
    // customize the series presentation settings
    QPen seriesPen(Qt::blue);
    seriesPen.setWidth(3);
//    series->setPen(seriesPen);
    //! [2]

    //! [add points to series]
    //add data points to the series
    series->append(QPointF(150, 100));
    series->append(QPointF(200, 130));
    series->append(QPointF(250, 120));
    series->append(QPointF(300, 140));
    series->append(QPointF(350, 160));
    //! [add points to series]

    QSplineSeries* series2 = new QSplineSeries;

    series2->append(QPointF(400, 120));
    series2->append(QPointF(450, 150));
    series2->append(QPointF(500, 145));
    series2->append(QPointF(550, 170));

//    series->append(QPointF(600, 190));
//    series->append(QPointF(650, 210));
//    series->append(QPointF(700, 190));
//    series->append(QPointF(750, 180));
//    series->append(QPointF(800, 170));
    QSplineSeries* series3 = new QSplineSeries;
        series3->append(QPointF(600, 190));
        series3->append(QPointF(650, 210));
        series3->append(QPointF(700, 190));
        series3->append(QPointF(750, 180));
        series3->append(QPointF(800, 170));

    //! [3]
    // create chart view
    QChart* chart = new QChart;
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->addSeries(series3);

    chart->setTitle("Spline chart example");
    chart->axisX()->setMax(1500);
    chart->axisY()->setMax(500);

    chart->setMinimumSize(800,600);
    //! [3]

    //! [4]
    //add new data point button
    QPushButton* addButton = new QPushButton("Add new point");
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNewPoint()));

    // remove the last data point in the series
    QPushButton* removeButton = new QPushButton("Remove point");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removePoint()));
    //! [4]

    //! [5]
    //butttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addStretch();

    QGridLayout* mainLayout = new QGridLayout;
    QChartView *chartView = new QChartView(chart);
    mainLayout->addWidget(chartView, 1, 0);
    mainLayout->addLayout(buttonsLayout, 1, 1);
    setLayout(mainLayout);
    //! [5]
}

//! [add point]
void SplineWidget::addNewPoint()
{
    if (series->count() > 0)
        series->append(QPointF(series->x(series->count() - 1) + 40 + qrand()%40, qAbs(series->y(series->count() - 1) - 50 + qrand()%100)));
    else
        series->append(QPointF(50, 50 + qrand()%50));
}
//! [add point]

//! [remove point]
void SplineWidget::removePoint()
{
    if (series->count() > 0)
        series->remove(QPointF(series->x(series->count() - 1), series->y(series->count() - 1)));
}
//! [remove point]

SplineWidget::~SplineWidget()
{
    
}

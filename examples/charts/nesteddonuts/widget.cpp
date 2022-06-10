// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include "widget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCore/QRandomGenerator>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTimer>

QT_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);

    //! [1]
    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart *chart = chartView->chart();
    chart->legend()->setVisible(false);
    chart->setTitle("Nested donuts demo");
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [1]

    //! [2]
    qreal minSize = 0.1;
    qreal maxSize = 0.9;
    int donutCount = 5;
    //! [2]

    //! [3]
    for (int i = 0; i < donutCount; i++) {
        QPieSeries *donut = new QPieSeries;
        int sliceCount =  3 + QRandomGenerator::global()->bounded(3);
        for (int j = 0; j < sliceCount; j++) {
            qreal value = 100 + QRandomGenerator::global()->bounded(100);
            QPieSlice *slice = new QPieSlice(QString("%1").arg(value), value);
            slice->setLabelVisible(true);
            slice->setLabelColor(Qt::white);
            slice->setLabelPosition(QPieSlice::LabelInsideTangential);
            connect(slice, &QPieSlice::hovered, this, &Widget::explodeSlice);
            donut->append(slice);
            donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
            donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
        }
        m_donuts.append(donut);
        chartView->chart()->addSeries(donut);
    }
    //! [3]

    // create main layout
    //! [4]
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);
    //! [4]

    //! [5]
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Widget::updateRotation);
    updateTimer->start(1250);
    //! [5]
}

Widget::~Widget()
{

}

//! [6]
void Widget::updateRotation()
{
    for (int i = 0; i < m_donuts.count(); i++) {
        QPieSeries *donut = m_donuts.at(i);
        qreal phaseShift =  -50 + QRandomGenerator::global()->bounded(100);
        donut->setPieStartAngle(donut->pieStartAngle() + phaseShift);
        donut->setPieEndAngle(donut->pieEndAngle() + phaseShift);
    }
}
//! [6]

//! [7]
void Widget::explodeSlice(bool exploded)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (exploded) {
        updateTimer->stop();
        qreal sliceStartAngle = slice->startAngle();
        qreal sliceEndAngle = slice->startAngle() + slice->angleSpan();

        QPieSeries *donut = slice->series();
        qreal seriesIndex = m_donuts.indexOf(donut);
        for (int i = seriesIndex + 1; i < m_donuts.count(); i++) {
            m_donuts.at(i)->setPieStartAngle(sliceEndAngle);
            m_donuts.at(i)->setPieEndAngle(360 + sliceStartAngle);
        }
    } else {
        for (int i = 0; i < m_donuts.count(); i++) {
            m_donuts.at(i)->setPieStartAngle(0);
            m_donuts.at(i)->setPieEndAngle(360);
        }
        updateTimer->start();
    }
    slice->setExploded(exploded);
}
//! [7]

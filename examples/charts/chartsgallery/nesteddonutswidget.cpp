// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "nesteddonutswidget.h"

#include <QChart>
#include <QChartView>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QLegend>
#include <QPieSeries>
#include <QPieSlice>
#include <QRandomGenerator>
#include <QTimer>

NestedDonutsWidget::NestedDonutsWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //! [1]
    auto chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart *chart = chartView->chart();
    chart->legend()->setVisible(false);
    chart->setTitle("Nested Donuts (Hover over segments to explode them)");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    //! [1]

    //! [2]
    qreal minSize = 0.1;
    qreal maxSize = 0.9;
    int donutCount = 5;
    //! [2]

    //! [3]
    for (int i = 0; i < donutCount; i++) {
        auto donut = new QPieSeries;
        int sliceCount =  3 + QRandomGenerator::global()->bounded(3);
        for (int j = 0; j < sliceCount; j++) {
            qreal value = 100 + QRandomGenerator::global()->bounded(100);
            auto slice = new QPieSlice(QString("%1").arg(value), value);
            slice->setLabelVisible(true);
            slice->setLabelColor(Qt::white);
            slice->setLabelPosition(QPieSlice::LabelInsideTangential);
            connect(slice, &QPieSlice::hovered, this, &NestedDonutsWidget::explodeSlice);
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
    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);
    //! [4]

    //! [5]
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &NestedDonutsWidget::updateRotation);
    m_updateTimer->start(1250);
    //! [5]
}

//! [6]
void NestedDonutsWidget::updateRotation()
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
void NestedDonutsWidget::explodeSlice(bool exploded)
{
    auto slice = qobject_cast<QPieSlice *>(sender());
    if (exploded) {
        m_updateTimer->stop();
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
        m_updateTimer->start();
    }
    slice->setExploded(exploded);
}
//! [7]

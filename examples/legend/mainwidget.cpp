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

#include "mainwidget.h"
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QBarSet>
#include <QBarSeries>
#include <QLegend>
#include <QFormLayout>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Create buttons for ui
    m_buttonLayout = new QGridLayout();
    QPushButton *detachLegendButton = new QPushButton("detach legend");
    connect(detachLegendButton, SIGNAL(clicked()), this, SLOT(detachLegend()));
    m_buttonLayout->addWidget(detachLegendButton, 0, 0);
    QPushButton *attachLegendButton = new QPushButton("attach legend");
    connect(attachLegendButton, SIGNAL(clicked()), this, SLOT(attachLegend()));
    m_buttonLayout->addWidget(attachLegendButton, 1, 0);

    QPushButton *addSetButton = new QPushButton("add barset");
    connect(addSetButton, SIGNAL(clicked()), this, SLOT(addBarset()));
    m_buttonLayout->addWidget(addSetButton, 2, 0);
    QPushButton *removeBarsetButton = new QPushButton("remove barset");
    connect(removeBarsetButton, SIGNAL(clicked()), this, SLOT(removeBarset()));
    m_buttonLayout->addWidget(removeBarsetButton, 3, 0);

    QPushButton *leftButton = new QPushButton("Align legend left");
    connect(leftButton, SIGNAL(clicked()), this, SLOT(setLegendLeft()));
    m_buttonLayout->addWidget(leftButton, 4, 0);

    QPushButton *rightButton = new QPushButton("Align legend right");
    connect(rightButton, SIGNAL(clicked()), this, SLOT(setLegendRight()));
    m_buttonLayout->addWidget(rightButton, 5, 0);

    QPushButton *topButton = new QPushButton("Align legend top");
    connect(topButton, SIGNAL(clicked()), this, SLOT(setLegendTop()));
    m_buttonLayout->addWidget(topButton, 6, 0);

    QPushButton *bottomButton = new QPushButton("Align legend bottom");
    connect(bottomButton, SIGNAL(clicked()), this, SLOT(setLegendBottom()));
    m_buttonLayout->addWidget(bottomButton, 7, 0);

    m_legendPosX = new QDoubleSpinBox();
    m_legendPosY = new QDoubleSpinBox();
    m_legendWidth = new QDoubleSpinBox();
    m_legendHeight = new QDoubleSpinBox();

    connect(m_legendPosX, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(m_legendPosY, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(m_legendWidth, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(m_legendHeight, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));

    QFormLayout* legendLayout = new QFormLayout();
    legendLayout->addRow("Horizontal position", m_legendPosX);
    legendLayout->addRow("Vertical position", m_legendPosY);
    legendLayout->addRow("Width", m_legendWidth);
    legendLayout->addRow("Height", m_legendHeight);
    m_legendSettings = new QGroupBox("Detached legend");
    m_legendSettings->setLayout(legendLayout);
    m_buttonLayout->addWidget(m_legendSettings);
    m_legendSettings->setVisible(false);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart, this);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_buttonLayout, 0, 0);
    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(m_mainLayout);

    createSeries();
}

void MainWidget::createSeries()
{
    m_series = new QBarSeries();
    addBarset();
    addBarset();
    addBarset();
    addBarset();

    m_chart->addSeries(m_series);
    m_chart->setTitle("Legend detach example");
//![1]
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
//![1]

    m_chart->axisY()->setNiceNumbersEnabled(true);
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWidget::showLegendSpinbox()
{
    m_legendSettings->setVisible(true);
    QRectF chartViewRect = m_chartView->rect();
    QRectF legendRect = m_chart->legend()->boundingRect();

    m_legendPosX->setMinimum(0);
    m_legendPosX->setMaximum(chartViewRect.width());
    m_legendPosX->setValue(150);

    m_legendPosY->setMinimum(0);
    m_legendPosY->setMaximum(chartViewRect.height());
    m_legendPosY->setValue(150);

    m_legendWidth->setMinimum(0);
    m_legendWidth->setMaximum(chartViewRect.width());
    m_legendWidth->setValue(150);

    m_legendHeight->setMinimum(0);
    m_legendHeight->setMaximum(chartViewRect.height());
    m_legendHeight->setValue(75);
}

void MainWidget::hideLegendSpinbox()
{
    m_legendSettings->setVisible(false);
}


void MainWidget::detachLegend()
{
//![2]
    QLegend *legend = m_chart->legend();
    legend->detachFromChart();

    m_chart->legend()->setBackgroundVisible(true);
    m_chart->legend()->setBrush(QBrush(QColor(128,128,128,128)));
    m_chart->legend()->setPen(QPen(QColor(192,192,192,192)));
//![2]

    showLegendSpinbox();
    updateLegendLayout();
    update();
}


void MainWidget::attachLegend()
{
//![3]
    QLegend *legend = m_chart->legend();
    legend->attachToChart();
    m_chart->legend()->setBackgroundVisible(false);
//![3]

    hideLegendSpinbox();
    update();
}

void MainWidget::addBarset()
{
    QBarSet *barSet = new QBarSet(QString("set ") + QString::number(m_series->count()));
    qreal delta = m_series->count() * 0.1;
    *barSet << QPointF(0.0 + delta, 1 + delta) << QPointF(1.0 + delta, 2 + delta) << QPointF(2.0 + delta, 3 + delta) << QPointF(3.0 + delta, 4 + delta);
    m_series->append(barSet);
}

void MainWidget::removeBarset()
{
    QList<QBarSet*> sets = m_series->barSets();
    if (sets.count() > 0) {
        m_series->remove(sets.at(sets.count()-1));
    }
}

void MainWidget::setLegendLeft()
{
    m_chart->legend()->setAlignment(Qt::AlignLeft);
}

void MainWidget::setLegendRight()
{
    m_chart->legend()->setAlignment(Qt::AlignRight);
}

void MainWidget::setLegendTop()
{
    m_chart->legend()->setAlignment(Qt::AlignTop);
}

void MainWidget::setLegendBottom()
{
    m_chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWidget::updateLegendLayout()
{
//![4]
    m_chart->legend()->setGeometry(m_legendPosX->value()
                                   ,m_legendPosY->value()
                                   ,m_legendWidth->value()
                                   ,m_legendHeight->value());
    m_chart->legend()->update();
//![4]
}

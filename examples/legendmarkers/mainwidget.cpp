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
#include <QLegend>
#include <QFormLayout>
#include <QLegendMarker>
#include <QLineSeries>
#include <QXYLegendMarker>
#include <qmath.h>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Create buttons for ui
    m_buttonLayout = new QGridLayout();

    QPushButton *addSliceButton = new QPushButton("add series");
    connect(addSliceButton, SIGNAL(clicked()), this, SLOT(addSeries()));
    m_buttonLayout->addWidget(addSliceButton, 1, 0);

    QPushButton *removeSliceButton = new QPushButton("remove series");
    connect(removeSliceButton, SIGNAL(clicked()), this, SLOT(removeSeries()));
    m_buttonLayout->addWidget(removeSliceButton, 2, 0);

    QPushButton *connectButton = new QPushButton("Connect markers");
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectMarkers()));
    m_buttonLayout->addWidget(connectButton, 3, 0);

    QPushButton *disConnectButton = new QPushButton("Disconnect markers");
    connect(disConnectButton, SIGNAL(clicked()), this, SLOT(disconnectMarkers()));
    m_buttonLayout->addWidget(disConnectButton, 4, 0);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart, this);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_buttonLayout, 0, 0);
    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(m_mainLayout);

    // Add few series
    addSeries();
    addSeries();
    addSeries();
    addSeries();

    // Set the title and show legend
    m_chart->setTitle("Legendmarker example");
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWidget::addSeries()
{
    QLineSeries *series = new QLineSeries();
    m_series.append(series);

    series->setName(QString("line " + QString::number(m_series.count())));

    // Make some sine wave for data
    QList<QPointF> data;
    int offset = m_chart->series().count();
    for (int i = 0; i < 360; i++) {
        qreal x = offset * 20 + i;
        data.append(QPointF(i, qSin(2.0 * 3.141592 * x / 360.0)));
    }

    series->append(data);
    m_chart->addSeries(series);

    if (m_series.count() == 1) {
        m_chart->createDefaultAxes();
    }
}

void MainWidget::removeSeries()
{
    // Remove last series from chart
    if (m_series.count() > 0) {
        QLineSeries *series = m_series.last();
        m_chart->removeSeries(series);
        m_series.removeLast();
        delete series;
    }
}

void MainWidget::connectMarkers()
{
//![1]
    // Connect all markers to handler
    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
        QObject::connect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
    }
//![1]
}

void MainWidget::disconnectMarkers()
{
//![2]
    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
    }
//![2]
}

void MainWidget::handleMarkerClicked()
{
//![3]
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);
//![3]

//![4]
    switch (marker->type())
//![4]
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
//![5]
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible());

        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true);
//![5]

//![6]
        // Dim the marker, if series is not visible
        QBrush labelBrush = marker->labelBrush();
        QColor color = labelBrush.color();

        if (marker->series()->isVisible()) {
            color.setAlphaF(1.0);
        } else {
            color.setAlphaF(0.5);
        }

        labelBrush.setColor(color);
        marker->setLabelBrush(labelBrush);
//![6]
        break;
        }
    default:
        {
        qDebug() << "Unknown marker type";
        break;
        }
    }
}

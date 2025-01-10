// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "legendmarkerswidget.h"

#include <QChart>
#include <QChartView>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QLegend>
#include <QLegendMarker>
#include <QLineSeries>
#include <QtMath>
#include <QXYLegendMarker>

LegendMarkersWidget::LegendMarkersWidget(QWidget *parent)
    : ContentWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart;
    m_chartView = new QChartView(m_chart, this);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout;
    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(m_mainLayout);

    // Add few series
    addSeries();
    addSeries();
    addSeries();
    addSeries();

    connectMarkers();

    // Set the title and show legend
    m_chart->setTitle("Legend Markers (Click on legend to interact)");
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chart->layout()->setContentsMargins(0, 0, 0, 0);
}

void LegendMarkersWidget::addSeries()
{
    auto series = new QLineSeries;
    m_series.append(series);

    series->setName(QString("line " + QString::number(m_series.count())));

    // Make some sine wave for data
    QList<QPointF> data;
    int offset = m_chart->series().count();
    for (int i = 0; i < 360; i++) {
        qreal x = offset * 20 + i;
        data.append(QPointF(i, qSin(qDegreesToRadians(x))));
    }

    series->append(data);
    m_chart->addSeries(series);

    if (m_series.count() == 1)
        m_chart->createDefaultAxes();
}

void LegendMarkersWidget::removeSeries()
{
    // Remove last series from chart
    if (m_series.count() > 0) {
        QLineSeries *series = m_series.last();
        m_chart->removeSeries(series);
        m_series.removeLast();
        delete series;
    }
}

void LegendMarkersWidget::connectMarkers()
{
//![1]
    // Connect all markers to handler
    const auto markers = m_chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &LegendMarkersWidget::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked,
                         this, &LegendMarkersWidget::handleMarkerClicked);
    }
//![1]
}

void LegendMarkersWidget::disconnectMarkers()
{
//![2]
    const auto markers = m_chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &LegendMarkersWidget::handleMarkerClicked);
    }
//![2]
}

void LegendMarkersWidget::handleMarkerClicked()
{
//![3]
    auto marker = qobject_cast<QLegendMarker *>(sender());
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
        qreal alpha = 1.0;

        if (!marker->series()->isVisible())
            alpha = 0.5;

        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);

        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);

        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);

//![6]
        break;
        }
    default:
        {
        qDebug("Unknown marker type");
        break;
        }
    }
}

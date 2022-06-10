// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "datasource.h"
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>

QT_USE_NAMESPACE

DataSource::DataSource(QObject *parent) :
    QObject(parent),
    m_index(-1)
{
}

void DataSource::update(QXYSeries *series, int seriesIndex)
{
    if (series) {
        const QList<QList<QPointF>> &seriesData = m_data.at(seriesIndex);
        if (seriesIndex == 0)
            m_index++;
        if (m_index > seriesData.count() - 1)
            m_index = 0;

        QList<QPointF> points = seriesData.at(m_index);
        // Use replace instead of clear + append, it's optimized for performance
        series->replace(points);
    }
}

void DataSource::handleSceneChanged()
{
    m_dataUpdater.start();
}

void DataSource::updateAllSeries()
{
    static int frameCount = 0;
    static QString labelText = QStringLiteral("FPS: %1");

    for (int i = 0; i < m_seriesList->size(); i++)
        update(m_seriesList->value(i), i);

    frameCount++;
    int elapsed = m_fpsTimer.elapsed();
    if (elapsed >= 1000) {
        elapsed = m_fpsTimer.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
        m_fpsLabel->setText(labelText.arg(QString::number(fps, 'f', 1)));
        m_fpsLabel->adjustSize();
        frameCount = 0;
    }
}

void DataSource::setInterval(int interval)
{
    m_dataUpdater.setInterval(interval);
}

void DataSource::startUpdates(QList<QXYSeries *> &seriesList, QLabel *fpsLabel, int interval)
{
    m_seriesList = &seriesList;
    m_fpsLabel = fpsLabel;

    m_dataUpdater.setInterval(interval);
    m_dataUpdater.setSingleShot(true);
    QObject::connect(&m_dataUpdater, &QTimer::timeout,
                     this, &DataSource::updateAllSeries);

    m_fpsTimer.start();

    m_data.resize(maxSeriesCount);
    updateAllSeries();
}

void DataSource::generateData(int seriesIndex, int rowCount, int colCount)
{
    // Remove previous data
    QList<QList<QPointF>> &seriesData = m_data[seriesIndex];
    seriesData.clear();
    seriesData.reserve(rowCount);

    qreal xAdjustment = 20.0 / (colCount * rowCount);
    qreal yMultiplier = 3.0 / qreal(maxSeriesCount);

    // Append the new data depending on the type
    qreal height = qreal(seriesIndex) * (10.0 / qreal(maxSeriesCount)) + 0.3;
    for (int i(0); i < rowCount; i++) {
        QList<QPointF> points;
        points.reserve(colCount);
        for (int j(0); j < colCount; j++) {
            qreal x(0);
            qreal y(0);
            // data with sin + random component
            y = height + (yMultiplier * qSin(M_PI / 50 * j)
                          + (yMultiplier * QRandomGenerator::global()->generateDouble()));
            // 0.000001 added to make values logaxis compatible
            x = 0.000001 + 20.0 * (qreal(j) / qreal(colCount)) + (xAdjustment * qreal(i));
            points.append(QPointF(x, y));
        }
        seriesData.append(points);
    }
}
